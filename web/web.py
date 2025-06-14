from flask import Flask, send_from_directory, render_template, request
import os
import csv

app = Flask(__name__, template_folder='.')
FOLDER_PATH = '/home/sdhbbb/workspace/FinalT/csv_database'

@app.route('/')
def index():
    files = os.listdir(FOLDER_PATH)
    files = [f for f in files if os.path.isfile(os.path.join(FOLDER_PATH, f))]
    return render_template('index.html', files=files)

@app.route('/download/<filename>')
def download(filename):
    return send_from_directory(FOLDER_PATH, filename, as_attachment=True)

@app.route('/view/<filename>')
def view_csv(filename):
    full_path = os.path.join(FOLDER_PATH, filename)

    if not os.path.isfile(full_path):
        return "can't find files.", 404

    table_data = []
    with open(full_path, 'r') as f:
        reader = csv.reader(f)
        for row in reader:
            table_data.append(row)

    return render_template('view_csv.html', filename=filename, table=table_data)
    
if __name__ == '__main__':
	app.run(host='0.0.0.0', port=8000, debug=True)

