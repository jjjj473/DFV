package com.example.screenstay;

import android.content.Context;
import android.os.PowerManager;

public class ScreenManager {
    private PowerManager.WakeLock wakeLock;
    private final Context context;

    public ScreenManager(Context context) {
        this.context = context;
    }

    public void keepScreenAwake() {
        if (wakeLock == null) {
            PowerManager powerManager = (PowerManager) context.getSystemService(Context.POWER_SERVICE);
            wakeLock = powerManager.newWakeLock(
                    PowerManager.SCREEN_DIM_WAKE_LOCK | PowerManager.ACQUIRE_CAUSES_WAKEUP,
                    "ScreenStay::FaceDetectionWakeLock");
        }
        if (!wakeLock.isHeld()) {
            wakeLock.acquire(10000L); // 10 seconds
        }
    }

    public void releaseWakeLockIfNeeded() {
        if (wakeLock != null && wakeLock.isHeld()) {
            wakeLock.release();
        }
    }
}
