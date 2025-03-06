import numpy as np
import sys
import networkx as nx
import matplotlib.pyplot as plt
from scipy.sparse import coo_matrix
import csv
# Funzione per leggere i dati sparsi (vettori e matrici) da un unico file CSV
def read_sparse_data(filename):
    data = { 'W': [], 'V': [], 'D': []}
    current_key = None

    with open(filename, 'r') as f:
        for line in f:
            if line.startswith('#'):  # Ignora le righe di commento
                continue
            if '@W' in line:
                current_key = 'W'
                print('@'+current_key)
                continue
            elif '@V' in line:
                current_key = 'V'
                print('@'+current_key)
                continue
            elif '@D' in line:
                current_key = 'D'
                print('@'+current_key)
                continue
            elements = line.strip().split(';')
          
            
            for  el in elements:
                if el=='':
                    continue

                singleval= el.split(',')
                print(singleval)
                value = float(singleval[2])
                indexr = int(singleval[0])
                indexc = int(singleval[1])
                # Determina quale sezione del file si sta leggendo
                

                # Aggiungi il valore e l'indice alla lista corretta
                if current_key:
                    data[current_key].append((value, int(indexr), int(indexc)))
    return data

def load_layer_labels(filename):
    layer_labels = {}
    with open(filename, newline='') as csvfile:
        
        for row in csvfile:
            elements = row.strip().split(';')
            #print(elements)
            
            for  el in elements:
                if el=='':
                    continue
                singleval= el.split(',')
                #print (singleval)
                index, name = int(singleval[0]), singleval[1]
                layer_labels[index] = name
    return layer_labels


# Funzione per convertire la lista sparsa in una matrice COO
def sparse_to_coo(matrix_data, rows, cols):
    values = []
    row_indices = []
    col_indices = []

    for value, row, col in matrix_data:
        values.append(value)
        row_indices.append(row)
        col_indices.append(col)

    return coo_matrix((values, (row_indices, col_indices)), shape=(rows, cols))

def float_to_mod8(value):
    return 1 + (abs(int(value)) % 7)

# Funzione per disegnare la rete neurale
def plot_neural_network(sensors, outputs, hidden_layer, W, V,D):
    # Creazione del grafo
    G_nn = nx.DiGraph()
    
    #Carica la mappa dall'enum esportato
    sensor_labels = load_layer_labels("../data_out/nnets/sense.csv")
    out_labels = load_layer_labels("../data_out/nnets/out.csv")
    node_colors = []
    labels = {} 
    
    # Aggiunta dei nodi con label
    for i in range(sensors):
        node_name = f"S{i}"
        G_nn.add_node(node_name, layer='input')
        node_colors.append("gold")
        labels[node_name] = sensor_labels[i]  # Etichetta

    for i in range(hidden_layer):
        node_name = f"N{i}"
        G_nn.add_node(node_name, layer='layer')
        node_colors.append("violet")
        labels[node_name] = f"N{i}"  # Etichetta

    for i in range(outputs):
        node_name = f"Y{i}"
        G_nn.add_node(node_name, layer='outputs')
        node_colors.append("orange")
        labels[node_name] = out_labels[i]  # Etichetta
 

    for i, j, value in zip(W.row, W.col, W.data):
        G_nn.add_edge(f"S{j}", f"N{i}", weight=value)

    for i, j, value in zip(V.row, V.col, V.data):
       G_nn.add_edge(f"N{j}", f"Y{i}", weight=value)   
    
    for i, j, value in zip(D.row, D.col, D.data):
        G_nn.add_edge(f"S{j}", f"Y{i}", weight=value,connectionstyle='arc3')       
    # Disegna il grafo
    pos = {}
    layer_spacing = 1


    # Posizionamento dei nodi
    for i in range((sensors)):
        pos[f"S{i}"] = (0, 5+i * layer_spacing)
    for i in range((hidden_layer)):
        pos[f"N{i}"] = (1, i * layer_spacing)
    for i in range((outputs)):
        pos[f"Y{i}"] = (2, i * layer_spacing)

    # Estrai i pesi degli archi
    weights = nx.get_edge_attributes(G_nn, "weight")
    
    normWeight=[]

    edge_colors = []
    for weight in weights.values():
        normalized_weight = np.clip(abs(weight), 0, 1) 
        normWeight.append(normalized_weight) 
        alpha = normalized_weight  
        color = (1 - (weight > 0), weight > 0, 0, alpha)  # (R, G, B, Alpha)
        edge_colors.append(color)
    
    isolated_nodes = [node for node in G_nn.nodes if G_nn.degree(node) == 0]
   # G_nn.remove_nodes_from(isolated_nodes)
    pos = nx.multipartite_layout(G_nn, subset_key="layer")
    options = {}


    pos_higher = {}
    x_off = 0  # offset on the y axis
    y_off=0.04
    for k, v in pos.items():
        pos_higher[k] = (v[0]+x_off, v[1]+y_off)


    nx.draw_networkx_nodes(G_nn, pos,node_size=70, label=labels,node_color=node_colors)
    nx.draw_networkx_labels(G_nn,pos_higher,labels=labels, font_size=3)
    nx.draw_networkx_edges(G_nn, pos,connectionstyle="arc3,rad=0.05",arrowsize=2,arrowstyle='-|>',width=normWeight,edge_color=edge_colors)
    #nx.draw(G_nn, pos,with_labels=True,arrowstyle='-', width=normWeight,node_size=120, node_color=node_colors, font_size=4,edge_color=edge_colors, font_weight='bold',**options)
    #edge_labels = nx.get_edge_attributes(G_nn, 'weight'
    #nx.draw_networkx_edge_labels(G_nn, pos, edge_labels=edge_labels)

    # Mostra il grafico
    plt.savefig("../data_out/images/rete_neurale.png", dpi=300, bbox_inches='tight')
 
    
   # nx.draw(G_nn, pos,with_labels=True,arrowstyle='-', node_size=120,  node_color=node_colors, font_size=4,edge_color=edge_colors, font_weight='bold',**options)
   
# Main function
def main():

    print ("@@@@@@@@@ NEURAL-SCOPE @@@@@@@@@ ")
    
    plt.figure(figsize=(7,7),facecolor='lavenderblush')
    ax= plt.gca()
    ax.axis('off')
    # Leggi i dati dal file CSV per il vettore e le matrici sparsi
    print("READING NET 0")
    data = read_sparse_data('../data_out/nnets/0_nn.csv')
    VsizeS = int(sys.argv[1])
    VsizeN = int(sys.argv[2])
    VsizeY = int(sys.argv[3])

    sensors=VsizeS
    hidden_layer=VsizeN
    outputs=VsizeY
    W = sparse_to_coo(data['W'], (hidden_layer), (sensors))
    V = sparse_to_coo(data['V'], (outputs), (hidden_layer))
    D = sparse_to_coo(data['D'], (outputs), (sensors))

    # Disegna la rete neurale
    plot_neural_network(sensors, outputs, hidden_layer, W, V,D)

# Esegui il programma
if __name__ == "__main__":
    main()
