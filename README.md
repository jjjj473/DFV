# DFV

This repository contains a simple dataset of HTML tags and their descriptions.
The text files can be used as reference material for learning about HTML or as
training data for an HTML-focused AI model.

Files included:
- `html_tags_overview.txt` — structural elements like `<html>`, `<head>`, and `<body>`
- `html_tags_text.txt` — tags for formatting and presenting textual content
- `html_tags_media.txt` — elements for images, audio, video, and other media
- `html_tags_forms.txt` — tags for building forms and gathering user input
- `javascript_overview.txt` — common DOM manipulation and scripting basics
- `javascript_text.txt` — functions for handling text content
- `javascript_media.txt` — scripts for controlling media elements
- `javascript_forms.txt` — scripts to process and validate form data
- `ai_model_basic.txt` — describes a model that assembles static sites using these datasets
- `ai_model_dynamic.txt` — outlines a dynamic application builder trained on the same files
- `custom_ai_model.py` — loads all datasets and answers queries with simple pattern matching
- `requirements.txt` — Python dependencies (includes the `torch` package)

Each JavaScript file mirrors the HTML tag lists with example actions showing how scripts interact with those tags.
The placeholder lines previously numbered as "Example entry" have been replaced with concise snippets of real JavaScript.

## Setup

Install the dependencies with:

```bash
pip install -r requirements.txt
```

The `custom_ai_model.py` script will use `torch` if available to perform simple vector matching across the datasets.
