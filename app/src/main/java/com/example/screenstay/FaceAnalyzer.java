package com.example.screenstay;

import androidx.camera.core.ImageAnalysis;
import androidx.camera.core.ImageProxy;

import com.google.mlkit.vision.common.InputImage;
import com.google.mlkit.vision.face.Face;
import com.google.mlkit.vision.face.FaceDetection;
import com.google.mlkit.vision.face.FaceDetector;

import java.util.List;

public class FaceAnalyzer implements ImageAnalysis.Analyzer {
    private final FaceDetector detector = FaceDetection.getClient();
    private final ScreenManager screenManager;

    public FaceAnalyzer(ScreenManager screenManager) {
        this.screenManager = screenManager;
    }

    @Override
    public void analyze(ImageProxy imageProxy) {
        if (imageProxy == null || imageProxy.getImage() == null) {
            if (imageProxy != null) {
                imageProxy.close();
            }
            return;
        }
        InputImage image = InputImage.fromMediaImage(imageProxy.getImage(), imageProxy.getImageInfo().getRotationDegrees());
        detector.process(image)
                .addOnSuccessListener(faces -> handleFaces(faces))
                .addOnCompleteListener(task -> imageProxy.close());
    }

    private void handleFaces(List<Face> faces) {
        if (faces != null && !faces.isEmpty()) {
            screenManager.keepScreenAwake();
        } else {
            screenManager.releaseWakeLockIfNeeded();
        }
    }
}
