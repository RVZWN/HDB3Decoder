# HDB3Decoder
A simple HDB3 Decoder

# What is HDB3?
HDB3 (European E-carrier) is used in all levels of the European E-carrier system, the high density bipolar of order 3 (HDB3) code replaces any instance of 4 consecutive 0 bits with one of the patterns "000V" or "B00V". The choice is made to ensure that consecutive violations are of differing polarity; i.e., separated by an odd number of normal + or − marks.

![image](https://github.com/user-attachments/assets/560a7836-a478-4f8e-8cda-50917517e2cc)

These rules are applied on the code as it is being built from the original string. Every time there are 4 consecutive zeros in the code they will be replaced by either 000−, 000+, +00+ or −00−. To determine which pattern to use, one must count the number of pluses (+) and the number of minuses (−) since the last violation bit V, then subtract one from the other. If the result is an odd number then 000− or 000+ is used. If the result is an even number then +00+ or −00− is used. To determine which polarity to use, one must look at the pulse preceding the four zeros. If 000V form must be used then V simply copies the polarity of last pulse, if B00V form must be used then B and V chosen will have the opposite polarity of the last pulse.

# VERY IMPORTANT!!
+ and - are determined in code by (+1 or 1 and -1) !!

# Examples
Here are some examples of bit streams codes with AMI and HDB3. All assume the same starting conditions: the previous 1 bit was −, and the previous violation was an even number of 1 bits ago. (E.g. the preceding bits could have been ++−.)

Input :	100001102
HDB3 :	+B00V−+0
Output : +−00−+−0

Input :	1010000011000011000000012
HDB3 :	+0−000V0+−B00V−+B00V000+
Output : +0−000−0+−+00+−+−00−000+

Input :	10100001000011000011100001111000010100002
HDB3 :	+0-000V+000V-+B00V-+-000V+-+-B00V+0-B00V
Output : +0-000-+000+-+-00-+-+000+-+-+-00-+0-+00+

Input :	100000000002
HDB3 :	+B00VB00V00
Output : +-00-+00+00
