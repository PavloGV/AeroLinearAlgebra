README

Author: Pavlo Vlastos

Date: 8/23/17

This README.txt outlines the format to write a text file to be used with the
SMCreator.c. The SMCreator.c creates a statemachine given a text file of the
follow format:

	Format: LevelNumber StateNumber Transition1 Transition2 ... TransitionN 

Example of text file for program:

	Input (text file): 

		L0 S0 S1
		L0 S1 S1 S2
		L0 S2 S3
		L0 S3 S1 S4
		L0 S4 S0

	Output (state machine main created using Input text file):
		
		...