class Solution(object):
    def recoverFromPreorder(self, S):
        # Usamos um índice de instância para percorrer a string S
        self.i = 0 
        self.n = len(S)
        
        # A profundidade inicial da raiz é 0
        return self._dfs(0, S)

    def _get_val_and_depth(self, S):
        """
        Função auxiliar para analisar a string S a partir do índice atual (self.i).
        Retorna (profundidade, valor_do_no) ou (None, None).
        """
        if self.i >= self.n:
            return None, None

        # 1. Contar a Profundidade (Traços)
        depth = 0
        while self.i < self.n and S[self.i] == '-':
            depth += 1
            self.i += 1
            
        # 2. Extrair o Valor do Nó
        start_index = self.i
        
        # Avança o índice enquanto houver dígitos
        while self.i < self.n and S[self.i].isdigit():
            self.i += 1
            
        # Extrai a substring do valor e converte para inteiro
        val_str = S[start_index:self.i]
        
        if not val_str:
            return None, None
            
        value = int(val_str)
        
        return depth, value

    def _dfs(self, required_depth, S):
        """
        Função recursiva para construir a árvore.
        """
        
        current_index = self.i
        
        # Tenta obter o próximo nó na string
        depth, value = self._get_val_and_depth(S)
        
        if depth is None:
            return None
            
        if depth != required_depth:
            # Backtracking: O nó não é o filho direto esperado.
            self.i = current_index
            return None

        node = TreeNode(value) 
        
        # 3. Chamada Recursiva para o Filho Esquerdo
        node.left = self._dfs(depth + 1, S)
        
        # 4. Chamada Recursiva para o Filho Direito
        node.right = self._dfs(depth + 1, S)
        
        return node