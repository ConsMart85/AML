clc

load reaction
betafit = nlinfitc(reactants,rate,@hougen,beta);
betafit

