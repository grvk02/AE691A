function[p,q] = next_state(i,j,ch)
    if ch == 'D'
        p = i+1;
        q=j;
    end 
    if ch == 'U'
        p = i-1;
        q=j;
    end 
    if ch == 'R'
        q = j+1;
        p=i;
    end 
    if ch == 'L'
        q = j-1;
        p=i;
    end 
end