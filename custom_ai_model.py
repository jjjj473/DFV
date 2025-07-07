import os

try:
    import torch
except ImportError:  # torch is optional
    torch = None

class CustomAIModule:
    def __init__(self, base_path=None):
        self.base_path = base_path or os.path.dirname(__file__)
        self.html_data = []
        self.js_data = []
        self.prompts = []
        self._load_datasets()
        if torch is not None:
            self._prepare_tensors()

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

    def _prepare_tensors(self):
        """Create simple bag-of-words vectors using torch."""
        all_lines = self.html_data + self.js_data + self.prompts
        vocab = set()
        for line in all_lines:
            vocab.update(line.lower().split())
        self.word_to_idx = {w: i for i, w in enumerate(sorted(vocab))}
        self.data_vectors = []
        for line in all_lines:
            vec = torch.zeros(len(self.word_to_idx))
            for word in line.lower().split():
                idx = self.word_to_idx.get(word)
                if idx is not None:
                    vec[idx] += 1
            self.data_vectors.append(vec)
        self.all_lines = all_lines

    def respond(self, query):
        """Return lines matching the query. Uses torch for vector search if available."""
        query_lower = query.lower()

        if torch is not None and hasattr(self, 'word_to_idx'):
            q_vec = torch.zeros(len(self.word_to_idx))
            for word in query_lower.split():
                idx = self.word_to_idx.get(word)
                if idx is not None:
                    q_vec[idx] += 1
            if q_vec.sum() > 0:
                sims = [torch.dot(q_vec, vec).item() for vec in self.data_vectors]
                top_idx = sorted(range(len(sims)), key=lambda i: sims[i], reverse=True)[:5]
                results = [self.all_lines[i] for i in top_idx if sims[i] > 0]
                if results:
                    return "\n".join(results)

        # Fallback to simple pattern matching
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
