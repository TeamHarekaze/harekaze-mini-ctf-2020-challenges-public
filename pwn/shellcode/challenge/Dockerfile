FROM ubuntu:20.10

RUN apt-get update && apt-get install -y xinetd \
    && useradd -m shellcode \
    && chown -R root:root /home/shellcode

ADD shellcode /home/shellcode/
ADD flag /home/shellcode/
ADD xinetd.conf /etc/xinetd.d/shellcode

RUN chmod 644 /home/shellcode/flag \
    && chmod 755 /home/shellcode/shellcode \
    && chmod 644 /etc/xinetd.d/shellcode

EXPOSE 30001

CMD ["/usr/sbin/xinetd", "-dontfork"]

