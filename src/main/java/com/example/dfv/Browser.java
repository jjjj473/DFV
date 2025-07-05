package com.example.dfv;

import javax.swing.*;
import javax.swing.event.HyperlinkEvent;
import javax.swing.event.HyperlinkListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

/**
 * Simple Swing-based web browser using JEditorPane.
 * Designed to mimic a classic look similar to older Windows browsers.
 */
public class Browser extends JFrame {
    private final JEditorPane display;
    private final JTextField addressBar;
    private final List<String> history;
    private int historyIndex;

    public Browser() {
        super("DFV Browser");
        try {
            // Use system look and feel to mimic native styling (e.g., Windows).
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception e) {
            // Fallback to default look and feel.
        }
        history = new ArrayList<>();
        historyIndex = -1;
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setSize(1024, 768);

        // Address bar and navigation buttons
        JToolBar toolBar = new JToolBar();
        JButton backButton = new JButton("<- Back");
        JButton forwardButton = new JButton("Forward ->");
        JButton refreshButton = new JButton("Refresh");
        addressBar = new JTextField();
        JButton goButton = new JButton("Go");

        backButton.addActionListener(e -> navigateBack());
        forwardButton.addActionListener(e -> navigateForward());
        refreshButton.addActionListener(e -> refresh());
        goButton.addActionListener(e -> navigate(addressBar.getText()));

        toolBar.setFloatable(false);
        toolBar.add(backButton);
        toolBar.add(forwardButton);
        toolBar.add(refreshButton);
        toolBar.add(addressBar);
        toolBar.add(goButton);

        // Web content display area
        display = new JEditorPane();
        display.setEditable(false);
        display.addHyperlinkListener(new LinkListener());
        JScrollPane scrollPane = new JScrollPane(display);

        getContentPane().add(toolBar, BorderLayout.NORTH);
        getContentPane().add(scrollPane, BorderLayout.CENTER);
    }

    private class LinkListener implements HyperlinkListener {
        @Override
        public void hyperlinkUpdate(HyperlinkEvent e) {
            if (e.getEventType() == HyperlinkEvent.EventType.ACTIVATED) {
                navigate(e.getURL().toString());
            }
        }
    }

    private void navigate(String url) {
        if (!url.startsWith("http")) {
            url = "http://" + url;
        }
        try {
            display.setPage(new URL(url));
            addressBar.setText(url);
            // Update history
            if (historyIndex < history.size() - 1) {
                history.subList(historyIndex + 1, history.size()).clear();
            }
            history.add(url);
            historyIndex = history.size() - 1;
        } catch (IOException e) {
            JOptionPane.showMessageDialog(this, "Unable to load page: " + e.getMessage(),
                    "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void refresh() {
        if (historyIndex >= 0) {
            navigate(history.get(historyIndex));
        }
    }

    private void navigateBack() {
        if (historyIndex > 0) {
            historyIndex--;
            navigate(history.get(historyIndex));
        }
    }

    private void navigateForward() {
        if (historyIndex < history.size() - 1) {
            historyIndex++;
            navigate(history.get(historyIndex));
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            Browser browser = new Browser();
            browser.setVisible(true);
        });
    }
}

