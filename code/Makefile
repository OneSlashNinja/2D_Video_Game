
ifeq ("$(shell whoami)", "malloy")
  CXX = clang++
else
  CXX = g++
endif
CXX_LINK = g++

# Warnings frequently signal eventual errors:
CXXFLAGS=`sdl-config --cflags` -g -W -Wall -Weffc++ -Wextra -pedantic -O0
LDFLAGS = `sdl-config --libs` -lSDL_ttf -lSDL_image -lSDL_mixer -lexpat

OBJS = \
	main.o \
	viewport.o \
	world.o \
	manager.o \
	toyBox.o \
	gamedata.o \
	parseXML.o \
  parseLsysXML.o \
	aaline.o \
	lsystem.o \
	clock.o \
	vector2f.o \
	spriteFactory.o \
	frameFactory.o \
	sprite.o \
  explodingSprite.o \
	chunk.o \
	multisprite.o \
	frame.o \
	ioManager.o \
	collisionStrategy.o \
	player.o \
  bullets.o \
	bullet.o \
	sound.o \
	smartSprite.o \
	menu.o \
	menuManager.o \
	menuItemsManager.o

EXEC = run

# $< refers to the first dependency
%.o: %.cpp
	$(CXX_LINK) $(CXXFLAGS) -c $< -o $@

# $@ refers to the target
$(EXEC): $(OBJS)
	g++ $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

main.o: main.cpp
manager.o: manager.cpp manager.h gamedata.h ioManager.h clock.h spriteFactory.h menuItemsManager.h toyBox.h
ioManager.o: ioManager.cpp ioManager.h
viewport.o: viewport.cpp viewport.h
world.o: world.cpp world.h
parseXML.o: parseXML.cpp parseXML.h
parseLsysXML.o: parseLsysXML.cpp parseLsysXML.h
aaline.o: aaline.cpp aaline.h
lsystem.o: lsystem.cpp lsystem.h ioManager.h parseLsysXML.h
gamedata.o: gamedata.cpp gamedata.h parseXML.h
spriteFactory.o: spriteFactory.cpp spriteFactory.h frameFactory.h sprite.h multisprite.h gamedata.h smartSprite.h
frameFactory.o: frameFactory.cpp frameFactory.h frame.h lsystem.h
clock.o: clock.cpp clock.h
vector2f.o: vector2f.cpp vector2f.h
frame.o: frame.cpp frame.h
sprite.o: sprite.cpp sprite.h drawable.h frame.h
multisprite.o: multisprite.cpp multisprite.h drawable.h frame.h gamedata.h
toyBox.o:toyBox.cpp toyBox.h drawable.h ioManager.h spriteFactory.h explodingSprite.h player.h collisionStrategy.h sound.h \
smartSprite.h aaline.h
frame.o: frame.cpp frame.h ioManager.h
explodingSprite.o: explodingSprite.cpp explodingSprite.h chunk.h
chunk.o: chunk.cpp chunk.h sprite.h gamedata.h
player.o: player.cpp player.h multisprite.h gamedata.h clock.h bullets.h
collisionStrategy.o: ioManager.h drawable.h
bullets.o: bullets.cpp bullets.h bullet.h gamedata.h spriteFactory.h
bullet.o: bullet.cpp bullet.h sprite.h
sound.o: sound.cpp sound.h
smartSprite.o: smartSprite.cpp multisprite.h ioManager.h
menu.o: menu.cpp menu.h ioManager.h vector2f.h frame.h parseXML.h
menuManager.o: menuManager.cpp menuManager.h menu.h ioManager.h clock.h parseXML.h manager.h
menuItemsManager.o: menuItemsManager.cpp menuItemsManager.h ioManager.h gamedata.h

clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)
