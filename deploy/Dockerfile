FROM debian:latest

RUN apt-get update && \
  apt-get install -y openssh-client g++ && \
  apt-get clean

# ADD do /   # write-only ssh key, omitted from this public repo — see README
ADD concur8.cc /
ADD run.sh /
ADD known_hosts /etc/ssh/ssh_known_hosts

CMD ["/run.sh"]
