set :stage, :production
server 'lavatory.antoinemary.me', user: 'deploy', roles: %w{app web}
set :branch, "master"