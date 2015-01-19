function AdjacencyMatrix = ERGraph(N,P)
    assert(P<1 && P>0, 'probability not valid')
    AdjacencyMatrix = double(rand(N) < P);
end


