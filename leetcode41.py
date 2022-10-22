class Solution:
    def firstMissingPositive(self, nums: List[int]) -> int:
        mx, mn = nums[0], nums[0]
        n = 0 # length
        for num in nums:
            n += 1
            mn = min(mn, num)
            mx = max(mx, num)
        
        # easy cases
        if mx <= 0:
            return 1
        if mn >= 2:
            return 1
        if 1 not in nums:
            return 1
        
        # preprocessing
        for (i, num) in enumerate(nums):
            if num <= 0:
                nums[i] = 1
            if num > n:
                nums[i] = 1
                
        # processing
        for num in nums:
            nums[num%(n+1) - 1] += (n+1) # flag, we've seen `num`
            
        # finding the solution
        for (i, num) in enumerate(nums):
            if num < (n+1): # we've not marked this one
                return i+1                
            
        return mx+1



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

### MON CODE FONCTIONNANT 2: 09/03/2022 11:53

class Solution:
    def firstMissingPositive(self, nums: List[int]) -> int:
        
        mx = max(nums)
        mn = min(nums)
        l = len(nums)
        
        if mx <= 0 or mn > 1:
            return 1
        # cas d'un unique élément strictement positif: évité
        
        
        # prétraitement
        for i in range(l): # préprocess: pas d'éléments nuls
            if nums[i] <= 0:
                nums[i] = mx # mettre les négatifs ou nuls = max (>0) testé à ce stade: on n'ajoute pas d'information
        
        # à partir de ce stade on peut commencer à encoder cf le raisonnement ci-dessous
        for n in nums:
            if abs(n) <= l: # <= longueur liste pour pouvoir l'encoder
                nums[abs(n)-1] = - abs(nums[abs(n)-1]) # décalage avec le -1       
        
        # enfin dernières étape on teste et on renvoie la réponse
        i = 0
        while i < l: # itération sur les indices pour encoder les entiers de 1 à l présents en convention python
            if nums[i] > 0:
                return i+1 # +1 pour compenser le décalage
            i += 1
        return l+1 # tous les entiers de 1 à l sont présents si on arrive jusqu'ici
                   # donc celui manquant est forcément l+1 cf 2è cas de la discussion ci-dessous
            
            
# PREUVE/RAISONNEMENT DE L'ALGO
        
    # PREMIERS TESTS
        # s'il n'y a pas d'éléments >0, renvoyer 1
        # si le minimum est > 1, renvoyer 1 
        
    # PREUVE POUR L'ENCODAGE
        # si le max des k entiers strictement positifs présents est <= au nombre d'éléments strictement positifs on peut les encoder sur le tableau (entre 1 et max sur tab) à coup sûr
        
        # si le max des k entiers strictement positifs présents est > au nombre d'éléments dans la liste (donc aussi >k car il peut y avoir des négatifs): on sait qu'il manquera au moins un entier entre 1 et k non "instancié" parmi les k-1 autres entiers positifs (faire un graphe de cases) donc on peut encoder sur les k premières positions (en effet, la fonction i €[|1,k|] -> tab[i] est au mieux injective et non surjective par hypothèse) et c'est ça qui permet d'encoder sur les k premières positions du tableau, donc sur le tableau (a fortiori si le tableau comporte des négatifs ce qui donne des places en plus)
        
        # dans les deux cas on n'encode que les instances dans le tableau <= au nombre d'éléments strictement positifs

### DERNIERE PROPOSITION SO FAR
class Solution:
    def firstMissingPositive(self, nums: List[int]) -> int:
        if 1 not in nums:
            return 1
        mx = max(nums)
        mn = min(nums)
        
        
        if mx <= 0 or mn > 1:
            return 1
        # cas d'un unique élément strictement positif: évité
        l = len(nums)
        
        # prétraitement
        for (i, num) in enumerate(nums): # préprocess: pas d'éléments nuls
            if num <= 0:
                nums[i] = mx # mettre les négatifs ou nuls = max (>0) testé à ce stade: on n'ajoute pas d'information
                
                
        # à partir de ce stade on peut commencer à encoder cf le raisonnement ci-dessous
        for n in nums:
            if abs(n) <= l: # <= longueur liste pour pouvoir l'encoder
                nums[abs(n)-1] = - abs(nums[abs(n)-1]) # décalage avec le -1  
                
                
        # enfin dernières étape on teste et on renvoie la réponse
        for (i, num) in enumerate(nums): # itération sur les indices pour encoder les entiers de 1 à l présents en convention python
            if num > 0:
                return i+1 # +1 pour compenser le décalage
        return l+1 # tous les entiers de 1 à l sont présents si on arrive jusqu'ici
                   # donc celui manquant est forcément l+1 cf 2è cas de la discussion ci-dessous