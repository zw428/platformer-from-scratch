FLAGS = -Wall
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

CC =g++ -g

BASE_OBJECTS = build/block.o build/collide_functions.o build/manager.o build/npc.o build/object.o build/player.o build/map.o build/chunk_prop.o build/alive.o build/attack.o build/image.o build/keys.o build/text.o build/shared_texture.o build/consts.o build/box.o build/trigger.o build/attack_box.o build/anim.o build/collider.o build/gravity_affected.o build/vel_accel.o build/mover.o

MAIN_OBJECTS = $(BASE_OBJECTS) build/main.o
TEST_OBJECTS = $(BASE_OBJECTS) build/test.o

unknown: $(MAIN_OBJECTS)
	$(CC) $^ $(LIBS) -o build/unknown

test: $(TEST_OBJECTS)
	$(CC) $^ $(LIBS) -o build/test

clean:
	rm build/*.o

build/block.o: block.cpp block.h
	$(CC) $(FLAGS) -c -o $@ $<

build/collide_functions.o: collide_functions.cpp collide_functions.h
	$(CC) $(FLAGS) -c -o $@ $<

build/manager.o: manager.cpp manager.h
	$(CC) $(FLAGS) -c -o $@ $<

build/npc.o: npc.cpp npc.h
	$(CC) $(FLAGS) -c -o $@ $<

build/object.o: object.cpp object.h
	$(CC) $(FLAGS) -c -o $@ $<

build/player.o: player.cpp player.h
	$(CC) $(FLAGS) -c -o $@ $<

build/map.o: map.cpp map.h
	$(CC) $(FLAGS) -c -o $@ $<

build/main.o: main.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/chunk_prop.o: chunk_prop.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/alive.o: alive.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/attack.o: attack.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/image.o: image.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/keys.o: keys.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/text.o: text.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/shared_texture.o: shared_texture.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/consts.o: consts.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/box.o: box.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/trigger.o: trigger.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/attack_box.o: attack_box.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/anim.o: anim.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/collider.o: collider.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/gravity_affected.o: gravity_affected.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/vel_accel.o: vel_accel.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/mover.o: mover.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/test.o: tests/test.cpp
	$(CC) $(FLAGS) -c -o $@ $<
