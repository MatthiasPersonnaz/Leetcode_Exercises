### DERNIÈRE PROPOSITION SO FAR
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
