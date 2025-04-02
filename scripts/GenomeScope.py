import csv
import random
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.image as mpimg

def generate_sample_csv(filename="chromosome_data.csv"):
    genes = [f"Gene_{i}" for i in range(1, 21)]  # 20 geni fittizi
    values = [random.randint(1, 100) for _ in genes]  # Valori casuali tra 1 e 100
    
    with open(filename, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(["gene_t", "valore"])  # Intestazione
        for gene, value in zip(genes, values):
            writer.writerow([gene, value])

def load_gene_data(filename="chromosome_data.csv"):
    gene_data = []
    with open(filename, mode='r') as file:
        reader = csv.reader(file)
        next(reader)  # Salta l'intestazione
        for row in reader:
            gene_data.append((row[0], int(row[1])))
    return gene_data

def map_values_to_colors(gene_data):
    cmap = plt.get_cmap("viridis")  # Mappa di colori
    min_val = min(v for _, v in gene_data)
    max_val = max(v for _, v in gene_data)
    color_map = {}
    
    for gene, value in gene_data:
        norm_value = (value - min_val) / (max_val - min_val)  # Normalizza tra 0 e 1
        color_map[gene] = cmap(norm_value)  # Assegna un colore
    
    return color_map

def draw_chromosome_with_background(gene_data, color_map, bg_image="chromosome.png"):
    img = mpimg.imread(bg_image)
    fig, ax = plt.subplots(figsize=(5, 10))
    ax.imshow(img, extent=[0, 1, 0, 1])
    
    y_positions = np.linspace(0.9, 0.1, len(gene_data))  # Posizioni verticali
    bar_width = 0.15
    
    for i, (gene, _) in enumerate(gene_data):
        color = color_map[gene]
        ax.add_patch(plt.Rectangle((0.4, y_positions[i]), bar_width, 0.04, color=color))
        ax.add_patch(plt.Rectangle((0.6, y_positions[i]), bar_width, 0.04, color=color))
    
    ax.set_xlim(0, 1)
    ax.set_ylim(0, 1)
    ax.axis("off")
    plt.title("Cromosoma con Alleli Colorati")
    plt.show()

if __name__ == "__main__":
    generate_sample_csv()
    gene_data = load_gene_data()
    color_map = map_values_to_colors(gene_data)
    draw_chromosome_with_background(gene_data, color_map)
