OPTIMIZED_CFLAGS = -O3 -ffast-math
CFLAGS = $(OPTIMIZED_CFLAGS) -Wdeprecated-declarations  \
	-I. -I..\..\allegro\include
CPPFLAGS = $(OPTIMIZED_CFLAGS) -fpermissive -Wdeprecated-declarations -std=c++11 \
-I. -I..\..\allegro\include -Iinclude -Idynamics
CC = gcc.exe
CPP = gpp.exe

.c.o: 
	$(CPP) $(CPPFLAGS) -c $< 2>&1 | tee -a compile.log

all: libbox2d.a

objs = src/collision/b2_broad_phase.o src/collision/b2_chain_shape.o \
		   src/collision/b2_circle_shape.o src/collision/b2_collide_circle.o \
		   src/collision/b2_collide_edge.o src/collision/b2_collide_polygon.o \
		   src/collision/b2_collision.o src/collision/b2_distance.o \
		   src/collision/b2_dynamic_tree.o src/collision/b2_edge_shape.o \
		   src/collision/b2_polygon_shape.o src/collision/b2_time_of_impact.o \
		   src/common/b2_block_allocator.o src/common/b2_draw.o \
		   src/common/b2_math.o src/common/b2_settings.o \
		   src/common/b2_stack_allocator.o src/common/b2_timer.o \
		   src/dynamics/b2_chain_circle_contact.o src/dynamics/b2_chain_polygon_contact.o \
		   src/dynamics/b2_circle_contact.o src/dynamics/b2_contact.o \
		   src/dynamics/b2_contact_manager.o src/dynamics/b2_contact_solver.o \
		   src/dynamics/b2_distance_joint.o src/dynamics/b2_edge_circle_contact.o \
		   src/dynamics/b2_edge_polygon_contact.o src/dynamics/b2_fixture.o \
		   src/dynamics/b2_friction_joint.o src/dynamics/b2_gear_joint.o \
		   src/dynamics/b2_island.o src/dynamics/b2_joint.o \
		   src/dynamics/b2_motor_joint.o src/dynamics/b2_mouse_joint.o \
		   src/dynamics/b2_polygon_circle_contact.o src/dynamics/b2_polygon_contact.o \
		   src/dynamics/b2_prismatic_joint.o src/dynamics/b2_pulley_joint.o \
		   src/dynamics/b2_revolute_joint.o src/dynamics/b2_weld_joint.o \
		   src/dynamics/b2_wheel_joint.o src/dynamics/b2_world.o \
		   src/dynamics/b2_world_callbacks.o src/dynamics/b2_body.o \
		   src/rope/b2_rope.o


libbox2d.a : $(objs)
	ar crs libbox2d.a $?

clean:
	rm -f src/collision/*.o 	
	rm -f src/common/*.o 	
	rm -f src/dynamics/*.o 	
	rm -f src/rope/*.o 	
	rm -f compile.log
	rm -f libbox2d.a
	



