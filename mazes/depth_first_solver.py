import recursive_backtrack_maze as rbm
import pygame
from pygame.locals import *


##Generating a maze for test_purposes
mazesize=21
test_maze=rbm.return_maze(mazesize)
seen=[]
s=[0,0]

##Depth-first solving a maze

def erase_doubles(seen):
    new_list = [] 
    for i in seen : 
        if i not in new_list: 
            new_list.append(i)
    return new_list
    
def isEnd(s,mazesize):
    if s == [mazesize-1,mazesize-1]:
        return True
    return False
    

def dFirst(s,maze,mazesize,seen):
    if isEnd(s,mazesize):
        return [s]

    else:
        for i in successeurs(s,maze,mazesize,seen):
            seen.append(i)
            res=dFirst(i,maze,mazesize,seen)
            
            if res != False:
                return [s]+res
                
        return False

def successeurs(s,maze,mazesize,seen):
    x=s[0]
    z=s[1]
    #print(seen)
    
    search_list = []
    if x < mazesize-1 and [x+1,z] in maze and [x+1,z] not in seen :
        search_list.append([x+1,z])
    if x > 0 and [x-1,z] in maze and [x-1,z] not in seen :
        search_list.append([x-1,z])
    if z < mazesize-1 and [x,z+1] in maze  and[x,z+1] not in seen :
        search_list.append([x,z+1])
    if z > 0 and [x,z-1] in maze and [x,z-1] not in seen :
        search_list.append([x,z-1])
    
    return search_list


def sbs_dFirst(s,maze,mazesize,seen,fenetre,seen_square):
    if isEnd(s,mazesize):
        return [s]

    else:
        for i in successeurs(s,maze,mazesize,seen):
            seen.append(i)
            
            seen=erase_doubles(seen)
            for i in seen:
                for event in pygame.event.get():
                        if event.type == pygame.QUIT: 
                            pygame.quit()
                fenetre.blit(seen_square,(int(i[0])*10,int(i[1])*10))
            pygame.display.flip()
            pygame.time.wait(1)
            
            
            
            res=sbs_dFirst(i,maze,mazesize,seen,fenetre,seen_square)
            
            
            if res != False:
                return [s]+res
                
        return False
    
def sbs_draw(mazesize):
    maze,fenetre = rbm.sbs_recur_backtrack_draw(mazesize,True)
    
    blue_square=pygame.image.load('blue_square.png').convert()
    blue_square=pygame.transform.scale(blue_square, (10,10))
    gray_square=pygame.image.load('gray_square.png').convert()
    gray_square=pygame.transform.scale(gray_square, (10,10))
    
    seen=[]
    s=[0,0]
    chemin=sbs_dFirst(s,maze,mazesize,seen,fenetre,gray_square)
    
    for i in chemin:
        for event in pygame.event.get():
                if event.type == pygame.QUIT: 
                    pygame.quit()
        fenetre.blit(blue_square,(int(i[0])*10,int(i[1])*10))
        pygame.display.flip()
        pygame.time.wait(10)
    
    
    while True:
        for event in pygame.event.get():
                if event.type == pygame.QUIT: 
                    pygame.quit()
    
    
    
        
    
    