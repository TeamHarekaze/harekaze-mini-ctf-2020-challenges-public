FROM ubuntu:20.10

RUN apt-get update && apt-get install -y xinetd \
    && useradd -m nmgame \
    && chown -R root:root /home/nmgame

ADD nmgame /home/nmgame/
ADD flag /home/nmgame/
ADD run.sh /home/nmgame/
ADD xinetd.conf /etc/xinetd.d/nmgame

RUN chmod 644 /home/nmgame/flag \
    && chmod 755 /home/nmgame/nmgame \
    && chmod 755 /home/nmgame/run.sh \
    && chmod 644 /etc/xinetd.d/nmgame

EXPOSE 40001

CMD ["/usr/sbin/xinetd", "-dontfork"]

