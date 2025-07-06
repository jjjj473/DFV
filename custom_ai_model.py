import os

class CustomAIModule:
    def __init__(self, base_path=None):
        self.base_path = base_path or os.path.dirname(__file__)
        self.html_data = []
        self.js_data = []
        self.prompts = []
        self._load_datasets()

    def _load_file(self, filename):
        path = os.path.join(self.base_path, filename)
        with open(path, 'r', encoding='utf-8') as f:
            return [line.strip() for line in f if line.strip() and not line.startswith('#')]

    def _load_datasets(self):
        html_files = [
            'html_tags_overview.txt',
            'html_tags_text.txt',
            'html_tags_media.txt',
            'html_tags_forms.txt'
        ]
        js_files = [
            'javascript_overview.txt',
            'javascript_text.txt',
            'javascript_media.txt',
            'javascript_forms.txt'
        ]
        prompt_files = [
            'prompt_dataset_one.txt',
            'prompt_dataset_two.txt'
        ]
        for f in html_files:
            self.html_data.extend(self._load_file(f))
        for f in js_files:
            self.js_data.extend(self._load_file(f))
        for f in prompt_files:
            self.prompts.extend(self._load_file(f))

    def respond(self, query):
        query_lower = query.lower()
        all_data = self.html_data + self.js_data + self.prompts
        matches = [line for line in all_data if query_lower in line.lower()]
        if matches:
            return "\n".join(matches[:5])
        return "No direct match found."

def interactive_mode():
    ai = CustomAIModule()
    print("Custom AI Model Loaded. Type 'quit' to exit.")
    while True:
        user_input = input('> ').strip()
        if user_input.lower() in {'quit', 'exit'}:
            break
        response = ai.respond(user_input)
        print(response)

if __name__ == '__main__':
    interactive_mode()
