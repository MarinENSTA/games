import pygame
from pygame.locals import *
from random import choice
from global_constants import *
import sys
import draw

def find_walls(c_cell,mazesize,walls,removed_walls):
    x=c_cell[0]
    z=c_cell[1]

    search_list = []
    if x < mazesize-1 and [x+1,z] not in walls and [x+1,z] not in removed_walls:
        search_list.append([x+1,z])
    if x > 0 and [x-1,z] not in walls and not [x-1,z] in removed_walls :
        search_list.append([x-1,z])
    if z < mazesize-1 and [x,z+1] not in walls and [x,z+1] not in removed_walls :
        search_list.append([x,z+1])
    if z > 0 and [x,z-1] not in walls and [x,z-1] not in removed_walls :
        search_list.append([x,z-1])
    
    return search_list

def count_visited(c_wall,mazesize,v_cells,u_cells):
    x=c_wall[0]
    z=c_wall[1]
    
    search_list = []
    if x < mazesize-1 and [x+1,z] in u_cells:
        search_list+=[[x+1,z],[x-1,z]]
    if z < mazesize-1 and [x,z+1] in u_cells:
        search_list+=[[x,z+1],[x,z-1]]
    
    if len(search_list) != 0:
        if search_list[0] in v_cells and search_list[1] not in v_cells :
            return search_list[1]
        elif search_list[0] not in v_cells and search_list[1] in v_cells :
            return search_list[0]
    
    return False
        
    

def prims(mazesize,sbs=False):
    
    #initialisation des variables utiles
    v_cells=[]
    walls=[]
    removed_walls=[]
    
    #initialisation de u_cells
    cells=[]
    A=range(int((mazesize+1)/2))
    for i in A:
        for j in A:
            cells.append([2*i,2*j])
    
    #initialisation de l'image
    if sbs==True:
        fenetre=init_maze_window(mazesize)
    
    c_cell=[10,10]
    v_cells.append(c_cell)
    walls=walls+find_walls(c_cell,mazesize,walls,removed_walls)
    
    while len(walls)!=0:
        c_wall=choice(walls)
        
        res=count_visited(c_wall,mazesize,v_cells,cells)
        if res != False :
            removed_walls.append(c_wall)
            v_cells.append(res)
            walls=walls+find_walls(res,mazesize,walls,removed_walls)
            
            if sbs==True:
                temp_maze=removed_walls+v_cells
                for i in temp_maze:
                    for event in pygame.event.get():
                            if event.type == pygame.QUIT: 
                                pygame.quit()
                    fenetre.blit(white_square,(int(i[0])*10,int(i[1])*10))
                pygame.display.flip()
                pygame.time.wait(1)
                
        
        walls.remove(c_wall)
    
    maze=v_cells+removed_walls
    if sbs==True:
        return maze,fenetre
    return maze

        
    
    
    
    