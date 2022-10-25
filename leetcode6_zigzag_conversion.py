# matthias
def convert(self, s, numRows):
    """
    :type s: str
    :type numRows: int
    :rtype: str
    """
    if numRows == 1:
        return s
    elif numRows == 2:
        ll = len(s)
        s1 = ''
        s2 = ''
        for i in range(ll):
            if i%2 == 0:
                s1 += s[i]
            else:
                s2 += s[i]
        return s1+s2
    else:
        ret_str = numRows*[''] 
        ll = len(s)
        for i in range(ll):
            series_number = i%(2*numRows-2)
            if series_number < numRows:
                ret_str[series_number] += s[i]
            else:
                nv_ind = series_number - numRows +1
                ret_str[numRows-1-nv_ind] += s[i]
        return ''.join(ret_str)