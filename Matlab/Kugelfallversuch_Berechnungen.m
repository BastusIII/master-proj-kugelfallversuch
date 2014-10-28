run Kugelfallversuch_Parameter.m

tf = sqrt((2*h)/g)
td = sqrt((2*(h+d+2*r))/g) - tf
tl = l/(R*2*pi*n)
tg = td + tf

n_max = l/(R*2*pi*td)

phi_d = td*n*2*pi;
phi_buffer = phi_l - phi_d

dPhi = n*tf*2*pi - phi_buffer/2