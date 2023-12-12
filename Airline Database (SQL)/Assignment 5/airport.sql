/* 
    Order of data:
    cityServed, faa, icao
    
    This requires a lookup in table cityState to find the associated zipCode
    values for column cityServed.
  
    An example insert statement would be:
  
    INSERT INTO airport (cityServed, faa, icao) VALUES ('12345', 'DAB', 'KDAB');    
*/

Daytona Beach, DAB, KDAB
Fort Lauderdale, FLL, KFLL
Fort Myers, RSW, KRSW	
Fort Walton Beach, VPS, KVPS
Gainesville, GNV, KGNV	
Jacksonville, JAX, KJAX
Key West, EYW, KEYW
Melbourne, MLB, KMLB
Miami, MIA, KMIA	
Orlando, MCO, KMCO	
Panama City, ECP, KECP
Pensacola, PNS, KPNS
Punta Gorda, PGD, KPGD
Sanford, SFB, KSFB	
Sarasota, SRQ, KSRQ
St. Petersburg, PIE, KPIE
Tallahassee, TLH, KTLH	
Tampa, TPA, KTPA	
West Palm Beach, PBI, KPBI