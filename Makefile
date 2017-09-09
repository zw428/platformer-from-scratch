FLAGS = -Wall
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

CC =g++ -g

BASE_OBJECTS = build/block.o build/collide_functions.o build/manager.o build/npc.o build/object.o build/player.o build/map.o build/chunk_prop.o build/alive.o build/attack.o build/image.o build/keys.o build/text.o build/shared_texture.o build/consts.o build/box.o build/trigger.o build/attack_box.o build/anim.o build/collider.o build/gravity_affected.o build/vel_accel.o build/mover.o build/friction.o build/resource_manager.o build/level_loader.o build/camera.o build/teleporter.o build/teleport_box.o build/death_box.o build/knockback_mult.o build/death.o build/disabled.o build/sound_player.o build/attackable.o

MAIN_OBJECTS = $(BASE_OBJECTS) build/main.o

TEST_OBJECTS = $(BASE_OBJECTS) build/test_main.o build/box_test.o build/alive_test.o build/attack_box_test.o build/attack_test.o build/attackable_test.o build/block_test.o build/camera_test.o build/chunk_prop_test.o

unknown: $(MAIN_OBJECTS)
	$(CC) $^ $(LIBS) -o build/unknown

test: $(TEST_OBJECTS)
	$(CC) $^ $(LIBS) -o build/test
	build/test

clean:
	rm build/*.o

build/block.o: block.cpp block.h object.cpp object.h image.cpp image.h manager.cpp manager.h
	$(CC) $(FLAGS) -c -o $@ $<

build/collide_functions.o: collide_functions.cpp collide_functions.h
	$(CC) $(FLAGS) -c -o $@ $<

build/manager.o: manager.cpp manager.h map.cpp map.h resource_manager.cpp resource_manager.h level_loader.cpp level_loader.h camera.cpp camera.h
	$(CC) $(FLAGS) -c -o $@ $<

build/npc.o: npc.cpp npc.h manager.cpp manager.h alive.cpp alive.h object.cpp object.h death.cpp death.h disabled.cpp disabled.h knockback_mult.cpp knockback_mult.h image.cpp image.h
	$(CC) $(FLAGS) -c -o $@ $<

build/object.o: object.cpp object.h gravity_affected.cpp gravity_affected.h
	$(CC) $(FLAGS) -c -o $@ $<

build/player.o: player.cpp player.h alive.cpp alive.h object.cpp object.h anim.cpp anim.h keys.cpp keys.h manager.cpp manager.h
	$(CC) $(FLAGS) -c -o $@ $<

build/map.o: map.cpp map.h
	$(CC) $(FLAGS) -c -o $@ $<

build/main.o: main.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/chunk_prop.o: chunk_prop.cpp chunk_prop.h
	$(CC) $(FLAGS) -c -o $@ $<

build/alive.o: alive.cpp alive.h attackable.cpp attackable.h
	$(CC) $(FLAGS) -c -o $@ $<

build/attack.o: attack.cpp attack.h sound_player.cpp sound_player.h attackable.cpp attackable.h
	$(CC) $(FLAGS) -c -o $@ $<

build/image.o: image.cpp image.h box.cpp box.h camera.cpp camera.h
	$(CC) $(FLAGS) -c -o $@ $<

build/keys.o: keys.cpp keys.h
	$(CC) $(FLAGS) -c -o $@ $<

build/text.o: text.cpp text.h shared_texture.cpp shared_texture.h
	$(CC) $(FLAGS) -c -o $@ $<

build/shared_texture.o: shared_texture.cpp shared_texture.h
	$(CC) $(FLAGS) -c -o $@ $<

build/consts.o: consts.cpp consts.h
	$(CC) $(FLAGS) -c -o $@ $<

build/box.o: box.cpp box.h
	$(CC) $(FLAGS) -c -o $@ $<

build/trigger.o: trigger.cpp trigger.h box.cpp box.h
	$(CC) $(FLAGS) -c -o $@ $<

build/attack_box.o: attack_box.cpp attack_box.h trigger.cpp trigger.h attack.cpp attack.h
	$(CC) $(FLAGS) -c -o $@ $<

build/anim.o: anim.cpp anim.h image.cpp image.h camera.cpp camera.h
	$(CC) $(FLAGS) -c -o $@ $<

build/collider.o: collider.cpp collider.h mover.cpp mover.h box.cpp box.h
	$(CC) $(FLAGS) -c -o $@ $<

build/gravity_affected.o: gravity_affected.cpp gravity_affected.h
	$(CC) $(FLAGS) -c -o $@ $<

build/vel_accel.o: vel_accel.cpp vel_accel.h
	$(CC) $(FLAGS) -c -o $@ $<

build/mover.o: mover.cpp mover.h friction.cpp friction.h
	$(CC) $(FLAGS) -c -o $@ $<

build/friction.o: friction.cpp friction.h vel_accel.cpp vel_accel.h
	$(CC) $(FLAGS) -c -o $@ $<

build/resource_manager.o: resource_manager.cpp resource_manager.h
	$(CC) $(FLAGS) -c -o $@ $<

build/level_loader.o: level_loader.cpp level_loader.h manager.cpp manager.h block.cpp block.h player.cpp player.h npc.cpp npc.h teleport_box.cpp teleport_box.h death_box.cpp death_box.h
	$(CC) $(FLAGS) -c -o $@ $<

build/camera.o: camera.cpp camera.h
	$(CC) $(FLAGS) -c -o $@ $<

build/teleporter.o: teleporter.cpp teleporter.h collider.cpp collider.h
	$(CC) $(FLAGS) -c -o $@ $<

build/teleport_box.o: teleport_box.cpp teleport_box.h trigger.cpp trigger.h
	$(CC) $(FLAGS) -c -o $@ $<

build/death_box.o: death_box.cpp death_box.h trigger.cpp trigger.h death.cpp death.h
	$(CC) $(FLAGS) -c -o $@ $<

build/knockback_mult.o: knockback_mult.cpp knockback_mult.h attackable.cpp attackable.h attack.cpp attack.h
	$(CC) $(FLAGS) -c -o $@ $<

build/death.o: death.cpp death.h
	$(CC) $(FLAGS) -c -o $@ $<

build/disabled.o: disabled.cpp disabled.h
	$(CC) $(FLAGS) -c -o $@ $<

build/sound_player.o: sound_player.cpp sound_player.h
	$(CC) $(FLAGS) -c -o $@ $<

build/attackable.o: attackable.cpp attackable.h
	$(CC) $(FLAGS) -c -o $@ $<


#TEST OBJECTS

build/test_main.o: test/test_main.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/box_test.o: test/box_test.cpp box.cpp box.h
	$(CC) $(FLAGS) -c -o $@ $<

build/alive_test.o: test/alive_test.cpp alive.cpp alive.h attack.cpp attack.h
	$(CC) $(FLAGS) -c -o $@ $<

build/attack_box_test.o: test/attack_box_test.cpp alive.h alive.cpp object.h object.cpp
	$(CC) $(FLAGS) -c -o $@ $<

build/attack_test.o: test/attack_test.cpp attack.cpp attack.h sound_player.cpp sound_player.h attackable.cpp attackable.h
	$(CC) $(FLAGS) -c -o $@ $<

build/attackable_test.o: test/attackable_test.cpp attackable.cpp attackable.h
	$(CC) $(FLAGS) -c -o $@ $<

build/block_test.o: test/block_test.cpp block.cpp block.h object.cpp object.h image.cpp image.h
	$(CC) $(FLAGS) -c -o $@ $<

build/camera_test.o: test/camera_test.cpp camera.cpp camera.h
	$(CC) $(FLAGS) -c -o $@ $<

build/chunk_prop_test.o: test/chunk_prop_test.cpp chunk_prop.cpp chunk_prop.h
	$(CC) $(FLAGS) -c -o $@ $<
