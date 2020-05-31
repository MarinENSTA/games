#Maze generation algorithms using pygame

import pygame
from pygame.locals import *
from random import choice
from global_constants import *
import sys
import draw
import time


##Recursive backtrack algorithm


#Recherche des voisins non déjà-vus
def find_neigh(c_cell,u_cells,gridsize):
    x=c_cell[0]
    z=c_cell[1]
    
    search_list = []
    if x < gridsize-2:
        search_list.append([x+2,z])
    if x > 1:
        search_list.append([x-2,z])
    if z < gridsize-2:
        search_list.append([x,z+2])
    if z > 1:
        search_list.append([x,z-2])
    
    neighbours = []
    for i in search_list :
        if i in u_cells:
            neighbours.append(i)
    
    return neighbours
    
    
#Fonction principale pour le calcul d'un labyrinthe de manière récursive
def recur_backtrack(c_cell,u_cells,v_cells,removed_walls,gridsize):
    v_cells.append(c_cell)
    
    while len(find_neigh(c_cell,u_cells,gridsize)) != 0:
        neighbours=find_neigh(c_cell,u_cells,gridsize)
        next_cell=choice(neighbours)
        
        #Some bias (working) ideas:
        #neighbours+=[neighbours[0]]*3
        #next_cell=find_neigh(c_cell,u_cells,gridsize)[-1]
        
        u_cells.remove(next_cell)
        wall=[(next_cell[0]-c_cell[0])/2+c_cell[0],(next_cell[1]-c_cell[1])/2+c_cell[1]]
        removed_walls.append(wall)
        u_cells,v_cells,removed_walls=recur_backtrack(next_cell,u_cells,v_cells,removed_walls,gridsize)
    
    return u_cells,v_cells,removed_walls

def sbs_recur_backtrack(c_cell,u_cells,v_cells,removed_walls,gridsize,fenetre):
    v_cells.append(c_cell)
    
    while len(find_neigh(c_cell,u_cells,gridsize)) != 0:
        neighbours=find_neigh(c_cell,u_cells,gridsize)
        next_cell=choice(neighbours)

        u_cells.remove(next_cell)
        wall=[(next_cell[0]-c_cell[0])/2+c_cell[0],(next_cell[1]-c_cell[1])/2+c_cell[1]]
        removed_walls.append(wall)
        
        white_cells=removed_walls+v_cells
        for i in white_cells:
            for event in pygame.event.get():
                    if event.type == pygame.QUIT: 
                        pygame.quit()
            fenetre.blit(white_square,(int(i[0])*10,int(i[1])*10))
        pygame.display.flip()
        pygame.time.wait(1)
        
        u_cells,v_cells,removed_walls=sbs_recur_backtrack(next_cell,u_cells,v_cells,removed_walls,gridsize,fenetre)
        
        
    
    return u_cells,v_cells,removed_walls

def sbs_recur_backtrack_draw(gridsize,sendOthers=False):
    #initialisation des variables utiles
    v_cells=[]
    c_cell=[0,0]
    removed_walls=[]
    
    #initialisation de u_cells
    u_cells=[]
    A=range(int((gridsize+1)/2))
    for i in A:
        for j in A:
            u_cells.append([2*i,2*j])
    del u_cells[0]
    
    #initialisation de la fenetre
    fenetre=init_maze_window(gridsize)

    u_cells,v_cells,removed_walls=sbs_recur_backtrack(c_cell,u_cells,v_cells,removed_walls,gridsize,fenetre)
        
    #Trace finale
    #Ne semble pas necessaire, au vu de la construction de sbs_recur_backtrack
    #Mais ne dessine malheureusement pas la derniere case du labyrinthe
    # ==> on se permet de tout redessiner une derniere fois.
    maze=removed_walls+v_cells
    last_cell=v_cells[-1]
    fenetre.blit(white_square,(int(last_cell[0])*10,int(last_cell[1])*10))
    fenetre.blit(green_square,(0,0))
    fenetre.blit(red_square,((gridsize-1)*10,(gridsize-1)*10))
    pygame.display.flip()
    
    if sendOthers==True:
        return maze,fenetre
    else:
        return maze
    
def return_recur_maze(gridsize):
    #initialisation des variables
    v_cells=[]
    c_cell=[0,0]
    removed_walls=[]
    
    #initialisation de u_cells, 'unknown cells'
    u_cells = []
    A = range(int((gridsize+1)/2))
    for i in A:
        for j in A:
            u_cells.append([2*i,2*j])
    del u_cells[0]
    
    #récupération du labyrinthe
    u_cells,v_cells,removed_walls=recur_backtrack(c_cell,u_cells,v_cells,removed_walls,gridsize)
    
    #renvoi du labyrinthe
    maze = v_cells+removed_walls
    return maze
    
    
##Same idea, just using a stack to avoid stack overflow
def stack_bactrack(gridsize,sbs=False):
    #initialisation des variables utiles
    v_cells=[]
    removed_walls=[]
    
    #initialisation de u_cells
    u_cells=[]
    A=range(int((gridsize+1)/2))
    for i in A:
        for j in A:
            u_cells.append([2*i,2*j])
    del u_cells[0]
    
    #initialisation de la pile
    stack=[]
    stack.append([0,0])
    k=0
    
    if sbs==True:
        fenetre=init_maze_window(gridsize)
    
    #Routinepour le calcul du labyrinthe
    while len(stack) != 0:
        k+=1
        c_cell=stack.pop()
        v_cells.append(c_cell)
        neighs=find_neigh(c_cell,u_cells,gridsize)
        
        if len(neighs) != 0:
            stack.append(c_cell)
            
            next_cell=choice(neighs)
            #next_cell=neighs[0]
            stack.append(next_cell)
            
            #NB : des tests on etes effectues en codant une fonction 'a la main'
            #a la place de remove, le resultat est TRES mauvais (temps de calcul double)
            u_cells.remove(next_cell)
            
            wall=[(next_cell[0]-c_cell[0])/2+c_cell[0],(next_cell[1]-c_cell[1])/2+c_cell[1]]
            removed_walls.append(wall)
        
            if sbs==True:                   
                fenetre.blit(white_square,(removed_walls[-1][0]))
                fenetre.blit(white_square,(v_cells[-1][0]))
                pygame.display.flip()
                pygame.time.wait(1)
        
        
    maze=v_cells+removed_walls
    if sbs==True:
        return maze,fenetre
    return maze
    
    #To use sizetracker function, comment above and de-comment following
    #return k,len(maze)



##Establishing some stats about this algorithm
def sizetracker(maxsize):
    begin_time=time.time()
    sizes=[]
    size=1
    
    import matplotlib.pyplot as plt
    
    len_mazes=[]
    len_loops=[]
    times=[]
    
    while size<maxsize:
        sizes.append(size)
        
        start = time.time()
        len_loop,len_maze=stack_bactrack(size)        
        end = time.time()
        
        len_mazes.append(len_maze)
        len_loops.append(len_loop)
        times.append(end-start)
        
        
        size+=50
    
    plt.subplot(211)
    plt.plot(sizes,len_mazes,label='Maze length')
    plt.plot(sizes,len_loops,label='Loop length')
    plt.legend()
    
    plt.subplot(212)
    plt.plot(sizes,times,label='time')
    
    plt.legend()
    plt.show()
    final_time=time.time()
    
    print("sum of unit times measured : ",sum(times),'s')
    print("total time measured : ",final_time-begin_time,'s')
    
        
    
    
    
    