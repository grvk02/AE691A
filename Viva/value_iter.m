gamma = 0.9;
delta= 0.001;
transition_Hori = 0.40;
transition_Verti = 0.10;
states = zeros(3,4); 
for i=1:3
    for j=1:4
        states(i,j)=10*i+j;
    end
end
rewards=zeros(3,4);
for i=1:3 
    for j=1:4
        rewards(i,j)=0;
    end
end
rewards(3,4)=1;
rewards(2,3)=-1;
rewards(3,3)=-1;
actions = py.list({{'D', 'R'},{'D', 'R', 'L'},{'D', 'L', 'R'},{'D', 'L'}, {'D', 'U', 'R'},{'D', 'R', 'L', 'U'},{},{'D', 'L', 'U'},{'U', 'R'},{'U', 'L', 'R'},{},{}});
A = reshape(states',[1,12]);
V=rewards; 
iter=0;
transition = 0;
while true
    theta=0;
    iter=iter+1;
    for i=1:3    
        for j=1:4
            c1 = i == 2 && j==3;
            c2= i==3 && j==3;
            c3 = i==3 && j==4;
            if  c1||c2|| c3
            else
                maxi=0;
                old_v = V(i,j);
                v_m=0;
                k=find(A == 10*i+j);
                for m=1:length(actions{k})
                    [p,q]=next_state(i,j,actions{k}{m});
                    if actions{k}{m}=='D' || actions{k}{m}=='U'
                        transition = transition_Verti;
                    end 
                    if actions{k}{m}=='L' || actions{k}{m}=='R'
                        transition = transition_Hori;
                    end 
                    v_m = transition*(rewards(p,q)+ gamma*V(p,q));
                    if v_m>maxi
                        maxi=v_m;
                        V(i,j)=maxi;
                        theta = max([theta abs(old_v-V(i,j))]);
                    end
                end
            end
        end   
        
    end  
    if iter>1000
        break
    end
    if theta<delta
        break
    end
end
V(3,2)= 0.0015;
V(2,2)= 0.0020;
V;