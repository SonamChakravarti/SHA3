
# first name a variable objects for all object files

objects =  ads_assgn_v1.o


# name a variable sources for all source files

sources = ads_assgn_v1.c

# now give target as lab1 with objects as variable dependencies + command line

assgn1: $(objects) 
	gcc -o assgn1 $(objects)

# list the dependencies for object files - those header files which help build objects



# how to build all object files from all dependent source files


$(objects): $(sources)
	gcc -c $(sources)

clean:
	rm $(objects) assgn1