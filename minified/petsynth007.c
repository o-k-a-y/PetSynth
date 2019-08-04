/**********

PetSynth 

A program that turns a Commodore PET 4032 series computer into a 
keyboard playable synthesizer.

-----

PetSynth v0.007 
by Chiron Bramberger
Copyright 2008, 2009 
Licence: GNU General Public License, version 2 (two)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; version 2 of the License.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
    
    More information about GNU can be found at the following website:
    http://www.gnu.org/
    
**********/


#include <stdlib.h>
#include <conio.h>
#include <peekpoke.h> 
#include <pet.h>

/*

some notes from commdore basic programming using pokes
oldschool I know!

10 poke 59467,16  :rem turn on port for sound  0 to turn off
20 poke 59466,15  :rem octave number
30 poke 59464,118 :rem note, 0 for no sound

poke 59464,0

*/




#define RUN_STOP 3




int main (void)
{
	// vars -----------------
	
	int counter = 0;
	int MAX_COUNTER = 250;
	char key_hit;
	int current_octave = 0xF;
	int distortion_set = 0; // 0 is off
	int distortion_set_2 = 0; // 0 is off
	int distortion_count = 0 ; // used to track what to do and stuff
	int distortion_count_2 = 0 ; // used to track what to do and stuff
	int distortion_2_value = 1;
	int vibrato_set = 0;
	int vibrato_value = 1;
	int vibrato_counter = 0;
	
	int last_note;
	int i = 0;	
	
	// inits ----------------
	clrscr();
	
	//Graphics Mode (lines touching)
	putchar(142); 
	
	puts ("                                       ");
        puts ("  ¦¦¦           ¦¦                     ");
        puts ("  ¦  ¦         ¦  ¦                    ");
        puts ("  ¦  ¦ ¦¦¦ ¦¦¦ ¦    ¦ ¦ ¦  ¦ ¦¦¦ ¦ ¦   ");
        puts ("  ¦¦¦  ¦    ¦   ¦   ¦ ¦ ¦¦ ¦  ¦  ¦ ¦   ");
        puts ("  ¦    ¦¦   ¦    ¦   ¦  ¦ ¦¦  ¦  ¦¦¦   ");
        puts ("  ¦    ¦    ¦     ¦  ¦  ¦  ¦  ¦  ¦ ¦   ");
        puts ("  ¦    ¦¦¦  ¦  ¦  ¦  ¦  ¦  ¦  ¦  ¦ ¦   ");
        puts ("  ¦             ¦¦                 ¦   ");
	puts ("");
	puts ("                                v0.007 ");
	puts ("by Chiron Bramberger  www.petsynth.org ");
	puts ("(c) 2008-2009               GNU GPL v2 ");
 	
	
	//text mode (with line spaces)
	putchar(14); 
	
	//uppercase/grphics mode (no space change) - POKE 59468,12 
	//POKE(0xE84C, 0xC);
	
	//lower/uppercase mode (not space change) - POKE 59468,14
	POKE(0xE84C, 0xE);	
	
	
	//printf ("\nPET Synth\n");
	
	POKE( 0xE84B, 0x10 );
	POKE( 0xE84A, current_octave); // octave 15
	POKE( 0xE848, 0x0 ); // freq off

	// main event loop
	for(;;){
		i = i + 1;	
		//printf("counter: %i\n", counter);
		
		if (kbhit()) {
			key_hit = cgetc();
			
			POKE( 0xE848, 0x00); // quick silence???

			if (key_hit == 'z') { // low C on keyboard, following piano layout
				last_note =  0xEE; // freq
			} else if (key_hit == 's') { // low c#, etc...
				last_note =  0xE0; // freq
			} else if (key_hit == 'x') {
				last_note =  0xD2;
			} else if (key_hit == 'd') {
				last_note =  0xC7;				
			} else if (key_hit == 'c') {
				last_note =  0xBC;	
			} else if (key_hit == 'v') {
				last_note =  0xB1;	
			} else if (key_hit == 'g') {
				last_note =  0xA8;	
			} else if (key_hit == 'b') {
				last_note =  0x9E;	
			} else if (key_hit == 'b') {
				last_note =  0x9E;
			} else if (key_hit == 'h') {
				last_note =  0x95;
			} else if (key_hit == 'n') {
				last_note =  0x8C;	
			} else if (key_hit == 'j') {				
				last_note =  0x85;
			} else if (key_hit == 'm') {
				last_note =  0x7D;	
			} else if (key_hit == ',') {
				last_note =  0x76;	
			} else if (key_hit == 'l') {
				last_note =  0x6E;					
			} else if (key_hit == ';') {
				last_note =  0x68;					
			} else if (key_hit == ':') {
				last_note =  0x63;	
			} else if (key_hit == '?') {
				last_note =  0x5D;	
								// upper piano keyboard
			
			} else if (key_hit == '@') {
				last_note = 0x85;	
			} else if (key_hit == 18) { // OFF_RVS
				last_note =  0x7D;				
				
			} else if (key_hit == 'q') {
				last_note =  0x76;	
			} else if (key_hit == '"') {
				last_note =  0x6E;	
			} else if (key_hit == 'w') {
				last_note =  0x68;	
			} else if (key_hit == '#') {
				last_note =  0x63;	
			} else if (key_hit == 'e') {
				last_note =  0x5D;	
			} else if (key_hit == 'r') {
				last_note =  0x58;	
			} else if (key_hit == '%') {
				last_note =  0x53;	
			} else if (key_hit == 't') {
				last_note =  0x4E;	
			} else if (key_hit == '\'') { // check this
				last_note =  0x4A;	
			} else if (key_hit == 'y') {
				last_note =  0x45;	
			} else if (key_hit == '&') {
				last_note =  0x41;	
			} else if (key_hit == 'u') {
				last_note =  0x3D;	
				
			} else if (key_hit == 'i') {
				last_note =  0x39;	
			} else if (key_hit == '(') {
				last_note =  0x36;	
			} else if (key_hit == 'o') {
				last_note =  0x33;	
			} else if (key_hit == ')') {
				last_note =  0x30;	
			} else if (key_hit == 'p') {
				last_note =  0x2D;	
//			} else if (key_hit == '|') { // fucking up poiting arrow
//				last_note =  0x5D;
			
	

			} else if (key_hit == RUN_STOP) { // run stop
				gotoxy(0,19);
				  puts("RUN STOP pressed. Exiting PetSynth.   ");
				  puts("Thanks for playing!                   ");
				
				return EXIT_SUCCESS;		
				

			// adjust octave	
			} else if (key_hit == '1') {
				current_octave--;
				POKE( 0xE84A, current_octave);  // oct down
				gotoy(20);
				printf("Current Octave Changed to: %i          \n", current_octave);
			} else if (key_hit == '2') {
				current_octave = 0xF;
				POKE( 0xE84A, current_octave); // oct reset
				gotoy(20);
				printf("Current Octave Changed to: %i          \n", current_octave);
			} else if (key_hit == '3') {
				current_octave++;
				POKE( 0xE84A, current_octave); // oct up
				gotoy(20);
				printf("Current Octave Changed to: %i          \n", current_octave);
				
				
			// adjust note length	
			} else if (key_hit == '4') {
				MAX_COUNTER = MAX_COUNTER - 10;
				gotoy(20);
				printf("Current Length Changed to: %i          \n", MAX_COUNTER);
			} else if (key_hit == '5') {
				MAX_COUNTER = 250;;
				gotoy(20);
				printf("Current Length Changed to: %i          \n", MAX_COUNTER);
			} else if (key_hit == '6') {
				MAX_COUNTER = MAX_COUNTER + 10;
				gotoy(20);
				printf("Current Length Changed to: %i          \n", MAX_COUNTER);
				
			// set distortion 1 mode 
			} else if (key_hit == '=') {
				if (distortion_set == 0) {
					distortion_set = 1;
				} else if  (distortion_set == 1) {
					distortion_set = 0;
				}//end if
				gotoy(20);
				printf("Current Distortion Changed to: %i      \n", distortion_set);

				
			
			
			// set distortion mode 2
			} else if (key_hit == '8') {
				if (distortion_set_2 == 0) {
					distortion_set_2 = 1;
					distortion_2_value = 1;
				} else if  (distortion_set_2 == 1) {
					distortion_set_2 = 0;
					distortion_count_2 = 0;
				}//end if
				gotoy(20);
				printf("Current Distortion 2 Changed to: %i    \n   ", distortion_set_2);

				
			// adjust note length	
			} else if (key_hit == '7') {
				if (distortion_2_value > 1) {
					distortion_2_value--;
				}//end if
				gotoy(20);
				printf("Distortion_2_value Changed to: %i      \n", distortion_2_value);
			} else if (key_hit == '9') {
				distortion_2_value++;
				gotoy(20);
				printf("Distortion_2_value Changed to: %i      \n", distortion_2_value);

				
			// vibrato
			} else if (key_hit == '.') {
				if (vibrato_set == 0) {
					vibrato_set = 1;
					vibrato_value = 1;
				} else if  (vibrato_set == 1) {
					vibrato_set = 0;
				}//end if
				gotoy(20);
				printf("Vibrato_set: %i                        \n", vibrato_set);
				      //--------------------------------------- 
			// adjust vibrato	
			} else if (key_hit == '0') {
				if (vibrato_value > 1) {
					vibrato_value--;
				}//end if
				gotoy(20);
				printf("vibrato_value Changed to: %i           \n", vibrato_value);
			} else if (key_hit == '-') {
				vibrato_value++;
				gotoy(20);
				printf("vibrato_value Changed to: %i           \n", vibrato_value);



			// notes off 
			} else if (key_hit == ' ') {
				counter = 0;
				last_note = 0;
				gotoy(20);
				printf("Notes off.                             \n", distortion_2_value);	


			// not notes, do nothing
			} else if (key_hit == 'a') {
				last_note = 0;
			} else if (key_hit == 'f') {
				last_note = 0;
			} else if (key_hit == 'k') {
				last_note = 0;
				
	
				

			} else if (key_hit == '!') {
				last_note = 0;	
			} else if (key_hit == '$') {
				last_note = 0;
			} else if (key_hit == '\\') {
				last_note = 0;
			} else if (key_hit == 95) { //left arrow
				last_note = 0;
				
			} else if (key_hit == 94) {// up arrow
				last_note = 0;
			} else if (key_hit == '[') {
				last_note = 0;				
			} else if (key_hit == '<') {
				last_note = 0;
			} else if (key_hit == ']') {
				last_note = 0;	
			} else if (key_hit == '>') {
				last_note = 0;
				
			} else if (key_hit == 147) {// SHIFT CLR_HOME
				putchar(147);
				last_note = 0;



				
			}//end if
			
			// START COUNTER!!!!
			counter = 1;
			POKE( 0xE848, last_note); // freq ON (note on)!
			
				
				
		}//end if (kbhit)
		
		
		
		
		

		
		/***** OLD
		// length of note
		for (pause = 0; pause < 250; pause++) {
			// do nothing
		}//end for			
		*****/
			
		if (counter == MAX_COUNTER) {
			POKE( 0xE848, 0x0 ); // freq off
			counter = 0;			
		}//end if
				
			
		if (counter > 0) {
			counter++;
		} //end if
		
		if (distortion_set == 1 && counter != 0) {
			if (current_octave < 255) {
				current_octave++;
			} else { 
				current_octave = 0;
			}//end if
			POKE( 0xE84A, current_octave); // octave 15
		}//end if
		
		if (distortion_set_2 == 1 && counter != 0 ) {

			
			if (distortion_count_2 == 0) {
				POKE( 0xE848, 0x0 ); // freq off
				POKE( 0xE848, last_note ); // freq back on
				distortion_count_2++;
			} else if (distortion_count_2 < distortion_2_value) {
				distortion_count_2++;
			} else if (distortion_count_2 == distortion_2_value) { 
				distortion_count_2 = 0;
			}//end if
			
		}//end if
		
		
		if (vibrato_set == 1 && counter != 0) {
			
			vibrato_counter++;
			
			switch(vibrato_counter) {

				case 0 : 
					POKE( 0xE848, last_note ); // freq										
				break;//end case
				

				case 20 : 
					POKE( 0xE848, last_note+vibrato_value ); // freq										
				break;//end case

				
				case 40 : 
					POKE( 0xE848, last_note ); // freq										
				break;//end case


				case 60 : 
					POKE( 0xE848, last_note-vibrato_value ); // freq										
				break;//end case
				
				
				case 80 : 
					vibrato_counter=0;										
				break;//end case
				
				
				default : 
					//POKE( 0xE848, last_note ); // freq
				break;//end case
				
				
				
			}//end switch
			
						
		}//end if
		
			
		
		//debug
		//printf("debug: %i\n", distortion_set_2);
		
		
		/*if (distortion_set_2 == 1 && distortion_count_2 == 1) {
			POKE( 0xE848, 0x0 ); // freq off
			POKE( 0xE848, last_note ); // freq back on
			distortion_count_2 = 0;
		} else {
			distortion_count_2++;
		}//end if */
	}

	POKE( 0xE84B, 0x0 ) ;

	return EXIT_SUCCESS;
}


