import re
import random

def add_useless_comments(code):
    lines = code.split('\n')
    with_comments = []
    for line in lines:
        with_comments.append(line)
        comment_probability = random.randint(1, 4)
        if comment_probability == 3:
            for _ in range(random.randint(1, 3)):
                comment = generate_random_comment()
                with_comments.append(comment)
    return '\n'.join(with_comments)

def add_unused_code(code):
    unused_code_dict = {
        1: """
def increment_value(self, x):
    return x + 1
""",
        2: """
def double_value(self, x):
    return x * 2
""",
        3: """
def square_value(self, x):
    return x ** 2
""",
        4: """    
def negate_value(self, x):
    return -x
"""
    }

    insert_at_beginning = '\n\n'.join([unused_code_dict[key].strip() for key in random.sample(unused_code_dict.keys(), k=random.randint(1, len(unused_code_dict)//2))])
    code = insert_at_beginning + '\n\n' + code

    return code

def generate_random_comment():
    start_phrases = ["It seems that", "Maybe", "I think", "Well,", "Actually,", "Interestingly,"]
    middle_phrases = ["the algorithm", "the function", "this part", "the code", "our approach", "the process"]
    end_phrases = ["needs improvement.", "is not very efficient.", "could be optimized.", "is quite complex.", "requires further analysis."]
    return f"#{random.choice(start_phrases)} {random.choice(middle_phrases)} {random.choice(end_phrases)}"


def add_empty_lines(code):
    num_empty_lines = random.randint(1, 10)
    empty_lines = '\n' * num_empty_lines

    lines = code.split('\n')
    random_insert_indices = random.sample(range(len(lines)), num_empty_lines)

    for index in sorted(random_insert_indices, reverse=True):
        lines.insert(index, '')

    return '\n'.join(lines) + empty_lines


def replace_tabs(file_path):
    with open(file_path, 'r') as file:
        code = file.read()

    code = re.sub(r'def\s+(\w+)\s*\(([^)]+)\):', lambda match: replace_args_tabs(match), code)
    code = re.sub(r'(?<=\s)(\w+)\s*=', lambda match: replace_variable_tabs(match), code)
    code = replace_variable_names(code)
    code = add_useless_comments(code)
    code = add_unused_code(code)
    code = add_empty_lines(code)

    output_file_path = "obfuscated_code.py"
    with open(output_file_path, 'w') as file:
        file.write(code)

    print("Obfuscation complete. Modified code saved as 'obfuscated_code.py'.")


def replace_args_tabs(match):
    func_name = match.group(1)
    args = match.group(2)
    args_list = args.split(',')
    replaced_args = []
    for arg in args_list:
        spaces = ' ' * random.randint(1, 20)
        replaced_args.append(f"{spaces}{arg.strip()}")
    return f'def {func_name}({", ".join(replaced_args)}):'


def replace_variable_tabs(match):
    variable = match.group(1)
    spaces = ' ' * random.randint(1, 20)
    return f'{variable}{spaces}='


def replace_variable_names(code):
    variable_names = {
        'private_key': 'old_name',
        'public_pem': 'num',
        'signature': 'variable_names',
        'license_key': 'spaces',
        'hashed_key': 'super_users',
        'correct_hash': 'replace_variable_tabs'
    }
    for old_name, new_name in variable_names.items():
        code = re.sub(rf'\b{old_name}\b', new_name, code)
    return code


if __name__ == "__main__":
    file_path = "installer.py"
    replace_tabs(file_path)
