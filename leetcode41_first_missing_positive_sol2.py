### MON CODE FONCTIONNANT 1: 09/03/2022 11:37

class Solution:
    def firstMissingPositive(self, nums: List[int]) -> int:
        
        mx = max(nums)
        mn = min(nums)
        if mx <= 0 or mn > 1:
            return 1
        # cas d'un unique élément strictement positif: évité
        
        
        # prétraitement
        nb_str_pos = 0 
        min_str_pos = 0
        for i in range(len(nums)): # préprocess: pas d'éléments nuls
            nb_str_pos += int(nums[i]>0) # compter le nombre de strict positifs
            
            if min_str_pos > nums[i] and nums[i]>0:
                min_str_pos = nums[i] # trouver le plus petit strictement positif
            
            if nums[i] <= 0:
                nums[i] = mx # mettre les négatifs ou nuls = max (>0) testé à ce stade: on n'ajoute pas d'information
        print(min_str_pos)
        print(nb_str_pos)
        print(nums)
            
        if min_str_pos > nb_str_pos:
            return 1
        
        # à partir de ce stade on peut commencer à encoder cf le raisonnement ci-dessous
        l = len(nums)
        for i in range(l):
            if abs(nums[i]) <= l: # <= longueur liste pour pouvoir l'encoder
                nums[abs(nums[i])-1] = - abs(nums[abs(nums[i])-1]) # décalage avec le -1
        
        print(nums) # après encodage
        
        
        # enfin dernières étape on teste et on renvoie la réponse
        i = 0
        while i < l: # itération sur les indices pour encoder les entiers de 1 à l présents en convention python
            if nums[i] > 0:
                return i+1 # +1 pour compenser le décalage
            i += 1
        return l+1 # tous les entiers de 1 à l sont présents si on arrive jusqu'ici
                   # donc celui manquant est forcément l+1 cf 2è cas de la discussion ci-dessous
