FLAGS = -Wall
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

CC =g++ -g

BASE_OBJECTS = build/block.o build/collide_functions.o build/manager.o build/npc.o build/object.o build/player.o build/map.o build/chunk_prop.o build/alive.o build/attack.o build/image.o build/keys.o build/text.o build/shared_texture.o build/consts.o build/box.o build/trigger.o build/attack_box.o build/anim.o build/collider.o build/gravity_affected.o build/vel_accel.o build/mover.o build/friction.o build/resource_manager.o build/level_loader.o build/camera.o build/teleporter.o build/teleport_box.o build/death_box.o build/knockback_mult.o build/death.o build/disabled.o build/sound_player.o

MAIN_OBJECTS = $(BASE_OBJECTS) build/main.o

TEST_OBJECTS = $(BASE_OBJECTS) build/test_main.o build/box_test.o build/alive_test.o build/attack_box_test.o

unknown: $(MAIN_OBJECTS)
	$(CC) $^ $(LIBS) -o build/unknown

test: $(TEST_OBJECTS)
	$(CC) $^ $(LIBS) -o build/test
	build/test

clean:
	rm build/*.o

build/block.o: block.cpp block.h
	$(CC) $(FLAGS) -c -o $@ $<

build/collide_functions.o: collide_functions.cpp
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

build/friction.o: friction.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/resource_manager.o: resource_manager.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/level_loader.o: level_loader.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/camera.o: camera.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/teleporter.o: teleporter.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/teleport_box.o: teleport_box.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/death_box.o: death_box.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/knockback_mult.o: knockback_mult.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/death.o: death.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/disabled.o: disabled.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/sound_player.o: sound_player.cpp
	$(CC) $(FLAGS) -c -o $@ $<


#TEST OBJECTS

build/test_main.o: test/test_main.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/box_test.o: test/box_test.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/alive_test.o: test/alive_test.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/attack_box_test.o: test/attack_box_test.cpp
	$(CC) $(FLAGS) -c -o $@ $<
