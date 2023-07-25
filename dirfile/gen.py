import sys
import random
import string

def generate_file(file_size):
    # Convert the input size string (e.g., '20M') to bytes
    size_units = {'B': 1, 'K': 1024, 'M': 1024**2, 'G': 1024**3}
    try:
        size = int(file_size[:-1]) * size_units[file_size[-1].upper()]
    except (ValueError, KeyError):
        print("Invalid file size format. Please use the format like '20M'.")
        return

    try:
        with open('file.in', 'w') as file:
            while size > 0:
                # Generate a random string of length min(size, 1024)
                chunk_size = min(size, 1024)
                random_text = ''.join(random.choices(string.ascii_letters + string.digits, k=chunk_size))
                file.write(random_text)
                size -= chunk_size
    except Exception as e:
        print(f"Error occurred while generating the file: {e}")
    else:
        print("File generated successfully.")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python generatefile.py <size>")
        print("Example: python generatefile.py 20M")
    else:
        file_size_arg = sys.argv[1]
        generate_file(file_size_arg)

