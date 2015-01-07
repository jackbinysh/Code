%construct a table of the possible cases
clear

CaseMatrix = [10 0.05 0.9 0.05 10^6;100 0.04 0.2 0.01 10^6 ;300 0.01 0.12 0.01 10^5 ;10^3 0.01 0.06 0.01 10^3];


for i = 2
    N = CaseMatrix(i,1);
    InitialP = CaseMatrix(i,2);
    FinalP = CaseMatrix(i,3);
    Step = CaseMatrix(i,4);
    NumRuns = CaseMatrix(i,5);
    Fraction = [0 0]';
    
    for P = (InitialP:Step:FinalP)
        Sum = 0;
        for k = 1:NumRuns
            LU = LUDecomp(ERGraph(N,P));
            Sum = Sum + LU.m_IsSingular;
        end
        Fraction(:,end) = [P,Sum/NumRuns];
    end

end
