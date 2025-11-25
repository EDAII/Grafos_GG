class Solution(object):
    def countCompleteComponents(self, n, edges):
        
        # 1. Construir a Lista de Adjacência
        adj = [[] for _ in range(n)]
        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)
            
        # Conjunto para rastrear nós já visitados
        visited = [False] * n
        
        # Contador para o número de componentes completos
        complete_component_count = 0

        # Função auxiliar de DFS aninhada (para simular o método auxiliar)
        # Retorna (num_vertices, num_arestas_contadas)
        def dfs(u, current_adj, current_visited):
            current_visited[u] = True
            
            num_vertices = 1
            # Contagem total do grau do nó atual
            num_edges_counted = len(current_adj[u]) 
            
            for v in current_adj[u]:
                if not current_visited[v]:
                    # Chamada recursiva e acumulação
                    V_sub, E_sub = dfs(v, current_adj, current_visited)
                    num_vertices += V_sub
                    num_edges_counted += E_sub
                    
            return num_vertices, num_edges_counted


        # 2. Iterar sobre todos os nós e encontrar componentes
        for i in range(n):
            if not visited[i]:
                # V = Vértices, E = Soma dos Graus (2 * Arestas Reais)
                V, E = dfs(i, adj, visited)
                
                # 3. Verificar a condição de Componente Completo (Clique)
                # Condição para clique: E (soma dos graus) == V * (V - 1)
                if E == V * (V - 1):
                    complete_component_count += 1
                    
        return complete_component_count