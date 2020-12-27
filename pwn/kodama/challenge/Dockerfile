FROM ubuntu:20.10

RUN apt-get update && apt-get install -y xinetd \
    && useradd -m kodama \
    && chown -R root:root /home/kodama

ADD kodama /home/kodama/
ADD flag /home/kodama/
ADD xinetd.conf /etc/xinetd.d/kodama

RUN chmod 644 /home/kodama/flag \
    && chmod 755 /home/kodama/kodama \
    && chmod 644 /etc/xinetd.d/kodama

EXPOSE 30003

CMD ["/usr/sbin/xinetd", "-dontfork"]

