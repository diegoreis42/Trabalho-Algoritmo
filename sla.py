from numpy import random

def generate_table(rows):
    table = []
    names = ['Bulbasaur', 'Charmander', 'Squirtle', 'Pikachu', 'Rattata', 'Mewtwo','Dragonite', 'Vaporeon', 'Gloom', 'Golbat', 'Zubat', 'Charizard', 'Furret', 'Silcoon', 'Roserade', 'Crobat', 'Caterpie', 'Metapod']     
    regioes = ['Kanto', 'Johto', 'Hoenn', 'Sinnoh', 'Hisui', 'Unova', 'Kalos', 'Alola', 'Galar',  'Paldea']
    mestres = ['Vanessa', 'Rafael', 'Minoru', 'Baldochi', 'Melise', 'Rod.Lima', 'Elisa', 'Philipe']
    ranking = ['A', 'B', 'C', 'D', 'E']
    
    for i in range(1, rows+1):
        name = random.choice(names)
        regiao = random.choice(regioes)
        rank  = random.choice(ranking)
        mestre = random.choice(mestres)
        fixed_number = f"{i:05d}"
        table.append([fixed_number, name, mestre, regiao, rank])
    
    random.shuffle(table)
    return table

# Generate table with 10,000 rows
table = generate_table(10000)

# Save the table to a text file
filename = "table.txt"
with open(filename, "w") as file:
    file.write("ID  Nome  Mestre  Regiao  Rank\n")
    for row in table:
        file.write(" ".join(map(str, row)) + "\n")

print(f"Table saved to {filename}.")
