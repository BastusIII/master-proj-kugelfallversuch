run Kugelfallversuch_Parameter.m
run Kugelfallversuch_Berechnungen.m

g = 9.81;

kugel_x = [];
kugel_v = [];

scheibe_phi = []; % Phi=0 bedeuted Kugel kann gerade durch das Loch durchfallen

dt = 0.0001;
c = 1; % loop counter

kugel_x(c) = 0.0;
kugel_v(c) = 0.0;
scheibe_phi(c) = -dPhi;

crash = 0;

while kugel_x < h+d+2*r
    c = c+1;
    
    % neuberechnen der Kugelposition und geschwindigkeit
    kugel_v(c) = kugel_v(c-1) + g*dt;
    kugel_x(c) = kugel_x(c-1) + ((kugel_v(c)+kugel_v(c-1))/2) * dt;
    
    % neuberechnen der Scheibenposition
    scheibe_phi(c) = scheibe_phi(c-1) + dt*2*pi*n;
    if scheibe_phi(c) > 2*pi
        scheibe_phi(c) = scheibe_phi(c) - 2*pi;
    end
    
    if kugel_x(c) > h
       if ~(scheibe_phi(c) >= 0 && scheibe_phi(c) <= phi_l)
           crash = 1;
           break
       end
    end
end

kugel_x(c)
kugel_v(c)
scheibe_phi(c)
c*dt

if crash == 1
   display('CRASH')
else
    display('JUHU')
end