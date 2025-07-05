# DFV

This project contains a basic Swing-based web browser written in Java.
The browser aims to provide a classic look similar to older Windows browsers.

## Building and Running

The project requires Java 21 or newer. To compile and run:

```bash
javac src/main/java/com/example/dfv/Browser.java
java -cp src/main/java com.example.dfv.Browser
```

If you have OpenJDK 24 installed, you can use `javac` and `java` from that JDK.

## Features
* Address bar with navigation buttons
* Back/Forward history
* Refresh page

This implementation uses `JEditorPane` for rendering HTML content, which
supports basic HTML but may not handle complex modern sites. For a more
powerful browser, consider integrating JavaFX WebView or another rendering
engine.
