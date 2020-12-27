FROM ubuntu:20.10

RUN apt-get update && apt-get install -y xinetd \
    && useradd -m nmgameex \
    && chown -R root:root /home/nmgameex

ADD nmgameex /home/nmgameex/
ADD flag /home/nmgameex/
ADD run.sh /home/nmgameex/
ADD xinetd.conf /etc/xinetd.d/nmgameex

RUN chmod 644 /home/nmgameex/flag \
    && chmod 755 /home/nmgameex/nmgameex \
    && chmod 755 /home/nmgameex/run.sh \
    && chmod 644 /etc/xinetd.d/nmgameex

EXPOSE 30002

CMD ["/usr/sbin/xinetd", "-dontfork"]

