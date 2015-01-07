classdef LUDecomp
    properties
        m_LUDecomp
        m_Permutation
        m_IsSingular
    end
    methods
        function Obj = LUDecomp(A)  
            
            N = length(A);
            Tolerance = 10^-9;
            
            Obj.m_LUDecomp = A;
            Obj.m_Permutation = (1:N);
            Obj.m_IsSingular = 0;
            
            % before attempting the decomposition, run a check for rows of
            % 0's 
            for i=1:N
                if all(~Obj.m_LUDecomp(i,:))
                    Obj.m_IsSingular = 1;
                    return;
                end
            end
                
            for j = 1:N
                for i = 1:j
                    temp = 0;
                    for k = 1:i-1
                        temp = temp + Obj.m_LUDecomp(i,k)*Obj.m_LUDecomp(k,j);
                    end
                    Obj.m_LUDecomp(i,j) = Obj.m_LUDecomp(i,j) - temp;
                end
                for i = j+1:N
                    temp = 0;
                    for k = 1:j-1
                        temp = temp + Obj.m_LUDecomp(i,k)*Obj.m_LUDecomp(k,j);
                    end
                    %we implement pivoting, so dont do the division here
                    Obj.m_LUDecomp(i,j) = (Obj.m_LUDecomp(i,j) - temp);
                end
                % pivoting
                [Maxvalue,Maxindex] = max(abs(Obj.m_LUDecomp(j:N,j)));
                if abs(Maxvalue) - Tolerance<0
                    Obj.m_IsSingular = 1;
                    return;
                end
                Maxindex = Maxindex + (j-1);
                Obj.m_LUDecomp([Maxindex,j],:) = Obj.m_LUDecomp([j, Maxindex],:);
                Obj.m_Permutation([Maxindex,j]) = Obj.m_Permutation([j, Maxindex]);
                % divide all of the others by our new diagonal element
                Obj.m_LUDecomp(j+1:N,j) = Obj.m_LUDecomp(j+1:N,j)/Obj.m_LUDecomp(j,j);
            end
        end              
    end   
end