function [ chi , sigmachisquared ] = jackknife(m)

n = length(m);
sigmasquaredM = var(m);
meanm = mean(m);
sigmasquaredMi = ((n-1)/(n-2))*sigmasquaredM -(1/(n-2))*((m-meanm).^2);

chi = sigmasquaredM;
sigmachisquared = sum((sigmasquaredMi-sigmasquaredM).^2);
end

