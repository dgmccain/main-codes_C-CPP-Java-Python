/*
    order of data:
    
    origin, destination, aircraft, departure, arrival
    
    This requires a lookup in table aircraft to find the associated ID
    values for column aircraft.
  
    An example insert statement would be:
  
    INSERT INTO flight (origin, destination, aircraft, departure, arrival) VALUES
    ('AAA', 'BBB', 20,'2020-10-06 09:00:00', '2021-04-01 08:00:00');
*/

DAB, FLL, Acro Sport, 2023-11-01 07:00:00, 2023-11-01 08:00:00
FLL, RSW, Sabre 40/60, 2023-11-01 08:00:00, 2023-11-01 09:00:00
RSW, VPS, A-500, 2023-11-01 09:00:00, 2023-11-01 10:00:00	
VPS, GNV, 1123 Westwind, 2023-11-01 10:00:00, 2023-11-01 11:00:00
GNV, JAX, Model 18 Turboliner, 2023-11-11 11:00:00, 2023-11-11 12:00:00	
JAX, EYW, GC-1B Globe, 2023-11-11 12:00:00, 2023-11-11 13:00:00
EYW, MLB, 747-300SR, 2023-11-04 13:00:00, 2023-11-04 14:00:00
MLB, MIA, EMB 175-E2, 2023-11-04 14:00:00, 2023-11-04 15:00:00
MIA, MCO, CitationJet, 2023-11-05 15:00:00, 2023-11-05 16:00:00	
MCO, ECP, CitationJet, 2023-11-05 16:00:00, 2023-11-05 17:00:00	
ECP, PNS, EMB 175-E2, 2023-11-06 17:00:00, 2023-11-06 18:00:00
PNS, PGD, 747-300SR, 2023-11-06 19:00:00, 2023-11-06 20:00:00
PGD, SFB, GC-1B Globe, 2023-11-07 07:00:00, 2023-11-07 08:00:00
SFB, SRQ, Model 18 Turboliner, 2023-11-07 09:00:00, 2023-11-07 10:00:00	
SRQ, PIE, 1123 Westwind, 2023-11-08 07:00:00, 2023-11-08 08:00:00
PIE, TLH, A-500, 2023-11-08 09:00:00, 2023-11-08 10:00:00
TLH, TPA, Sabre 40/60, 2023-11-09 07:00:00, 2023-11-09 08:00:00	
TPA, PBI, Acro Sport, 2023-11-09 10:00:00, 2023-11-09 11:00:00	
PBI, DAB, PA-18-150 Super Cub, 2023-11-10 11:00:00, 2023-11-10 12:00:00