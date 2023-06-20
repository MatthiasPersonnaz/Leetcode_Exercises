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
