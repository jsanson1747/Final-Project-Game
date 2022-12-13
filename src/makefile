game:			game.o sprite.o player.o scene.o mapManager.o
				g++ game.o sprite.o player.o scene.o mapManager.o -o game.exe

game.o:			game.cpp Scene.h Sprite.h Player.h MapManager.h
				g++ -c game.cpp
	
sprite.o:		Sprite.cpp Sprite.h Scene.h SDL2/SDL.h
				g++ -c Sprite.cpp

player.o:		Player.cpp Player.h Sprite.h Scene.h
				g++ -c Player.cpp

scene.o:		Scene.cpp scene.h SDL2/SDL.h SDL_image.h MapManager.h
				g++ -c Scene.cpp

mapManager.o:	MapManager.cpp MapManager.h Scene.h Sprite.h
				g++ -c MapManager.cpp

clean:
				rm *.o
				rm game.exe

run:			game
				./game.exe