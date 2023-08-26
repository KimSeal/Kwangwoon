
import numpy as np
#initial value map
init_world = [[-1, -1, -1, -1, -1, -1, -1],
             [-1, -1, -1, -1, -1, -1, -1],
             [-1, -1, -1, -1, -1, -1, -1],
             [-1, -1, -1, -1, -1, -1, -1],
             [-1, -1,   -1, -1, -1, -1, -1],
             [-1, -1,   -1, -1, -1, -1, -1],
             [-1, -1, -1, -1, -1, -1, -1]]
#initial reward of 7*7 grid world
reward_world = [[-1, -1, -100, -1, -1, -1, -1],
             [-1, -1, -100, -1, -1, -1, -1],
             [-1, -1,   -1, -1, -1, -1, -1],
             [-1, -1,   -1, -1, -100, -100, -1],
             [-1, -1,   -1, -1, -1, -1, -1],
             [-1, -1,   -1, -1, -1, -1, -1],
             [-1, -1, -100, -100, -1, -1, -1]]
#function to policy evalution
def policy_evaluation2(gridworld, reward, discount, policy):
    #variable of result
    sub_table = np.zeros([7, 7], dtype=float)
    #take each value of next table
    sub_value = 0
    #about 7*7 matrix
    for y in range(7):
            for x in range(7):
                sub_value = 0
                #when action go to end of matrix, return to their value
                #up action
                if y==0 :
                    sub_value += policy[y][x][0] * (discount*gridworld[y][x]+ reward[y][x])
                else :
                    sub_value += policy[y][x][0] *(discount*gridworld[y-1][x]+ reward[y-1][x])
                #down action
                if y==6 :
                    sub_value += policy[y][x][1] * (discount*gridworld[y][x]+ reward[y][x])
                else :
                    sub_value += policy[y][x][1] *(discount*gridworld[y+1][x]+ reward[y+1][x])
                #left action
                if x==0 :
                    sub_value += policy[y][x][2] * (discount*gridworld[y][x]+ reward[y][x])
                else :
                    sub_value += policy[y][x][2] * (discount*gridworld[y][x-1] + reward[y][x-1])
                #right action
                if x==6 :
                    sub_value += policy[y][x][3] * (discount*gridworld[y][x] + reward[y][x])
                else :
                    sub_value += policy[y][x][3] * (discount*gridworld[y][x+1] + reward[y][x+1])
                #add value
                sub_table[y][x] =  float(sub_value) 
                sub_value = 0    
    #end point setting
    sub_table[6][6] = 0
    return sub_table

#function to policy improvement
def policy_improvement(gridworld, reward, discount):
    #save policy result
    sub_table = np.zeros([7, 7, 4], dtype=float)
    #about 7*7 matrix
    for y in range(7):
            for x in range(7):
                #take value of each action to direction
                direction =[0,0,0,0]
                dir_val =[0,0,0,0]
                #upcase
                if y==0 :
                    dir_val[0] += discount * gridworld[y][x]+  reward[y][x]
                else :
                    dir_val[0] += discount* gridworld[y-1][x]+ reward[y-1][x]
                #down case
                if y==6 :
                    dir_val[1] += discount* gridworld[y][x]+ reward[y][x]
                else :
                    dir_val[1] += discount* gridworld[y+1][x]+ reward[y+1][x]
                #left case
                if x==0 :
                    dir_val[2] += discount* gridworld[y][x]+ reward[y][x]
                else :
                    dir_val[2] += discount* gridworld[y][x-1]+ reward[y][x-1]
                #right case
                if x==6:
                    dir_val[3] += discount* gridworld[y][x]+ reward[y][x]
                else :
                    dir_val[3] += discount* gridworld[y][x+1]+ reward[y][x+1]
                #take number of max value
                maxnum = 0
                for z0 in range(4):
                    if max(dir_val) == dir_val[z0]:
                        maxnum += 1
                #put divided value about each direction value(greedy)
                for z in range(4):
                    if max(dir_val) == dir_val[z]:
                        direction[z] = 1/maxnum
                sub_table[y][x] = direction
    #about end point
    sub_table[6][6]= [0,0,0,0]

    return sub_table

#function to do value iteration
def value_iter(gridworld, reward, discount):
    #matrix to save next matrix
    sub_table = np.zeros([7, 7], dtype=float)
    sub_value = 0
    #about 7&7 matrix
    for y in range(7):
            for x in range(7):
                #each direction value
                u_val=0
                d_val=0
                l_val=0
                r_val=0
                #upside value case
                if y==0 :
                    u_val += discount* gridworld[y][x]+ reward[y][x]
                else :
                    u_val += discount*gridworld[y-1][x]+ reward[y-1][x]
                #downside value case
                if y==6 :
                    d_val += discount*gridworld[y][x]+ reward[y][x]
                else :
                    d_val += discount*gridworld[y+1][x]+ reward[y+1][x]
                #leftside value case
                if x==0 :
                    l_val += discount*gridworld[y][x]+ reward[y][x]
                else :
                    l_val += discount*gridworld[y][x-1] + reward[y][x-1]
                #rightside value case
                if x==6 :
                    r_val += discount*gridworld[y][x] + reward[y][x]
                else :
                    r_val += discount*gridworld[y][x+1] + reward[y][x+1]
                #find max of value about each direction(greedy)
                sub_table[y][x] =  max(u_val, d_val, l_val, r_val) 
                sub_value = 0    
    #about end point
    sub_table[6][6] = 0

    return sub_table

#function to print string about policy
def policy_print(input_direction):
    direction_str = ['U', 'D', 'L', 'R']
    dir_str = []
    #about 7*7 grid world
    for y in range(7):
        dir_str = []
        for x in range(7):
            max=0
            direct = 0
            str_1=''
            #find max value of action
            for z in range(4):
                if(input_direction[y][x][z] > max):
                    max = input_direction[y][x][z]
                    #direct = z
            #when start case
            #if(x==0 and y== 0):
            #    str_1+='S'
            #when end case
            if (x==6 and y== 6):
                str_1+='E'
            #about other cases
            else:
                for k in range(4):
                    if(input_direction[y][x][k]==max):
                        str_1 += direction_str[k]
            dir_str.append(str_1)
        print(dir_str)

input_direction=np.zeros([7, 7, 4], dtype=float)
input_direction2=np.zeros([7, 7, 4], dtype=float)
#set random policy
for k1 in range(7):
    for k2 in range(7):
        for k3 in range(4):
            input_direction[k1][k2][k3] = 0.25  #every direction move probability make same
            input_direction2[k1][k2][k3] = 0.25  #every direction move probability make same

#input_table=np.zeros([7, 7], dtype=float)
input_table = init_world
#policy evaluation
print('policy_evaluation & policy_improvement')
#do policy evaluation for appropriate number
for k in range(3000): 
    #print number of function do
    if(k==2999 or k==2998 or k==0 or k==1 or k==2 or k==3):
        print(k)
    #print value of table
    for y in range(7):
        if(k==2999 or k==2998 or k==0 or k==1 or k==2 or k==3):
            print(input_table[y])
    #print policy
    if(k==2999 or k==2998 or k==0 or k==1 or k==2 or k==3):
        policy_print(input_direction)
    #calculate policy evalutation and policy 
    input_table = policy_evaluation2(input_table, reward_world, 1, input_direction2)
    input_direction = policy_improvement(input_table, reward_world, 1)


#policy_iteration
print('policy_iteration')
#input_table=np.zeros([7, 7], dtype=float)
input_table = init_world

#initialize table of value
input_direction = input_direction2
input_table_sub = np.zeros([7, 7], dtype=float)

#do policy evaluation for appropriate number
for k in range(3000):
    if(k==2999 or k==2998 or k==0 or k==1 or k==2 or k==3):
        print(k)
    #print value of table
    for y in range(7):
        if(k==2999 or k==2998 or k==0 or k==1 or k==2 or k==3):
            print(input_table[y])
    #print policy
    if(k==2999 or k==2998 or k==0 or k==1 or k==2 or k==3):
        policy_print(input_direction)
    #calculate policy evalutation and policy and update when next try
    input_table = init_world.copy()
    input_table_sub = np.zeros([7, 7], dtype=float)
    while(not((input_table_sub == input_table).all())):
        input_table_sub = input_table.copy()
        input_table = policy_evaluation2(input_table, reward_world, 1, input_direction)
    input_direction = policy_improvement(input_table, reward_world, 1)


#test value iteration
print()
print('value_iteration')
#initialize table of value
#input_table=np.zeros([7, 7], dtype=float)
input_table = init_world

input_direction = input_direction2
#do value iteration for appropriate number
for k in range(3000):
    if(k==2999 or k==2998 or k==0 or k==1 or k==2 or k==3):
        print(k)
    #print value of table
    for y in range(7):
        if(k==2999 or k==2998 or k==0 or k==1 or k==2 or k==3):
            print(input_table[y])
    #print policy
    if(k==2999 or k==2998 or k==0 or k==1 or k==2 or k==3):
        policy_print(input_direction)
    #calculate next table and policy
    input_table = value_iter(input_table, reward_world, 1)
    input_direction = policy_improvement(input_table, reward_world, 1)

    