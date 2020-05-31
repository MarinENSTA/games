import recursive_backtrack_maze as rbm
import prims_algorithm_maze as pm
import pygame
from pygame.locals import *
from global_constants import *

##Depth-first solving a maze

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
    #print(s)
    #print(mazesize)
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


def sbs_dFirst(s,maze,mazesize,seen,fenetre):
    if isEnd(s,mazesize):
        return [s]

    else:
        for i in successeurs(s,maze,mazesize,seen):
            if i not in seen:
                seen.append(i)
            for i in seen:
                for event in pygame.event.get():
                        if event.type == pygame.QUIT: 
                            pygame.quit()
                fenetre.blit(gray_square,(int(i[0])*10,int(i[1])*10))
            pygame.display.flip()
            pygame.time.wait(1)
            
            
            
            res=sbs_dFirst(i,maze,mazesize,seen,fenetre)
            
            
            if res != False:
                return [s]+res
                
        return False
    
def sbs_draw(mazesize):
    maze,fenetre = pm.prims(mazesize,True)
    #maze,fenetre = rbm.stack_bactrack(mazesize,True)
    
    seen=[]
    s=[0,0]
    chemin=sbs_dFirst(s,maze,mazesize,seen,fenetre)
    
    for i in chemin:
        for event in pygame.event.get():
                if event.type == pygame.QUIT: 
                    pygame.quit()
        fenetre.blit(blue_square,(int(i[0])*10,int(i[1])*10))
        pygame.display.flip()
        pygame.time.wait(5)
    
    
    while True:
        for event in pygame.event.get():
                if event.type == pygame.QUIT: 
                    pygame.quit()
    
    
    
        
    
    