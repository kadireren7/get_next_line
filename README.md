*This project has been created as part of the 42 curriculum by kaaltint.*

# Get Next Line

## Description

Get Next Line, bir file descriptor üzerinden veriyi satır satır okumayı amaçlayan 42 projesidir.

Projenin temel amacı aşağıdaki prototipe sahip bir fonksiyon geliştirmektir:

```c
char	*get_next_line(int fd);
```

Fonksiyon her çağrıldığında verilen file descriptor üzerinden bir sonraki satırı döndürür.

Dönen satır, dosyada mevcutsa satır sonundaki `\n` karakterini de içerir. Dosyanın son satırı `\n` ile bitmiyorsa, son satır yine doğru şekilde döndürülür.

Okunacak başka veri kalmadığında veya bir hata oluştuğunda fonksiyon `NULL` döndürür.

Bu proje özellikle şu konuların anlaşılmasını amaçlar:

- `read()` sistem çağrısı
- File descriptor mantığı
- Static değişkenler
- Dinamik bellek yönetimi
- Buffer kullanımı
- Birden fazla fonksiyon çağrısı arasında verinin korunması
- Dosyanın tamamını belleğe almadan parça parça okunması

## Mandatory Part

Mandatory bölümde kullanılan dosyalar:

- `get_next_line.c`
- `get_next_line_utils.c`
- `get_next_line.h`

Projede Libft kullanılmamaktadır.

Subject tarafından izin verilen external fonksiyonlar:

- `read`
- `malloc`
- `free`

## Bonus Part

Bonus bölümünde `get_next_line()` aynı anda birden fazla file descriptor'ın okuma durumunu takip edebilir.

Her file descriptor kendi kalan verisini korur ve diğer descriptor'ların okuma durumunu etkilemez.

Bonus bölümünde tek bir static değişken kullanılır. Bu değişken, file descriptor numarasına göre ayrı stash değerleri tutan bir pointer dizisidir.

Bonus dosyaları:

- `get_next_line_bonus.c`
- `get_next_line_utils_bonus.c`
- `get_next_line_bonus.h`

## Algorithm

Bu implementasyonda veri üç temel yapı üzerinden yönetilir: `buffer`, `stash` ve `line`.

### Buffer

`buffer`, `read()` fonksiyonunun o anda okuduğu geçici veri alanıdır.

```c
read(fd, buffer, BUFFER_SIZE);
```

`read()` string sonuna otomatik olarak `\0` eklemediği için buffer `BUFFER_SIZE + 1` byte olarak ayrılır.

Okuma işleminden sonra:

```c
buffer[bytes_read] = '\0';
```

ile buffer geçerli bir C string haline getirilir.

### Stash

`stash`, okunmuş fakat henüz kullanıcıya döndürülmemiş veriyi saklar.

Bir `read()` çağrısı sadece mevcut satırı değil, sonraki satırın bir bölümünü de okuyabilir.

Örneğin dosyada:

```text
Hello
World
```

bulunurken bir okuma sonucunda bellekte şu veri oluşabilir:

```text
Hello\nWor
```

Bu durumda `get_next_line()` yalnızca:

```text
Hello\n
```

satırını döndürmelidir.

Geri kalan:

```text
Wor
```

verisi kaybedilmemelidir. Bu nedenle kalan veri stash içerisinde tutulur ve bir sonraki `get_next_line()` çağrısında kullanılmaya devam edilir.

### Line

`line`, kullanıcıya döndürülecek mevcut satırdır.

Stash içerisinde `\n` bulunduğunda, newline karakteri dahil olacak şekilde ilk satır ayrılır. Kullanılmış bölüm stash'ten çıkarılır ve yalnızca bir sonraki çağrıda gerekecek veri saklanır.

## Algorithm Flow

Bir `get_next_line(fd)` çağrısının genel akışı:

```text
get_next_line(fd)
        |
        v
stash mevcut mu?
        |
        +---- hayır ----> boş stash oluştur
        |
        v
stash içinde '\n' var mı?
        |
        +---- hayır ----> read()
        |                   |
        |                   v
        |              buffer'a oku
        |                   |
        |                   v
        |              stash ile birleştir
        |                   |
        +-------------------+
        |
        v
ilk satırı stash'ten çıkar
        |
        v
kalan veriyi stash olarak sakla
        |
        v
line döndür
```

Okuma işlemi stash içerisinde newline bulunana veya dosyanın sonuna ulaşılana kadar devam eder.

Bu sayede dosyanın tamamı tek seferde belleğe alınmaz.

## Why This Algorithm?

`read()` satır bazlı değil, byte bazlı çalışır. `BUFFER_SIZE` ise dosyadaki satır uzunluklarından bağımsızdır.

Bu nedenle:

- Bir satır birden fazla `read()` çağrısı gerektirebilir.
- Bir `read()` çağrısı birden fazla satırdan veri getirebilir.
- Sonraki satıra ait veri kaybedilmeden saklanmalıdır.
- Fonksiyon çağrıları arasında kalan verinin korunması gerekir.

Static stash kullanımı, fonksiyon sona erdikten sonra bile henüz döndürülmemiş verinin korunmasını sağlar.

## Helper Functions

### `ft_strlen`

Bir string'in uzunluğunu hesaplar.

### `ft_strchr`

Bir string içerisinde belirli bir karakteri arar. Bu projede özellikle stash içerisinde `\n` bulunup bulunmadığını kontrol etmek için kullanılır.

### `ft_strjoin`

İki string'i yeni ayrılmış bir bellek alanında birleştirir. Yeni okunan buffer'ın mevcut stash'e eklenmesinde kullanılır.

### `init_stash`

İlk kullanım sırasında boş bir stash oluşturur.

### `append_buffer`

Yeni okunan buffer'ı stash ile birleştirir ve eski stash belleğini serbest bırakır.

## Instructions

Mandatory bölüm aşağıdaki gibi derlenebilir:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line.c get_next_line_utils.c
```

`BUFFER_SIZE` farklı değerlerle de test edilebilir:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 \
get_next_line.c get_next_line_utils.c
```

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 \
get_next_line.c get_next_line_utils.c
```

## Testing

Proje aşağıdaki durumlarla test edilmiştir:

- `BUFFER_SIZE=1`
- `BUFFER_SIZE=4`
- `BUFFER_SIZE=42`
- `BUFFER_SIZE=9999`
- Normal çok satırlı dosyalar
- Boş dosya
- Tek newline içeren dosya
- Birden fazla boş satır
- Sonunda newline bulunmayan dosya
- Uzun satırlar
- Bonus bölümünde birden fazla file descriptor'ın dönüşümlü okunması
- Norminette
- Valgrind ile memory leak kontrolleri

## Resources

Proje sırasında yararlanılan kaynaklar:

- `man 2 read`
- `man 3 malloc`
- `man 3 free`
- 42 Get Next Line subject
- 42 Norm dokümantasyonu

## AI Usage

Bu proje geliştirilirken AI desteğinden yararlanıldı.

AI; proje mantığını anlamak, `read()`, file descriptor, static değişken ve stash
yapısını açıklamak, algoritmayı adım adım tartışmak, kodu Norm kurallarına göre
gözden geçirmek, test senaryoları ve edge case'ler hazırlamak için kullanıldı.

Ayrıca bu README dosyasının hazırlanması ve düzenlenmesi sırasında da AI
yardımından yararlanıldı.

AI tarafından sağlanan açıklamalar, kod önerileri ve dokümantasyon önerileri
doğrudan doğruluğu varsayılarak kullanılmadı; proje derleme, Norminette, farklı
`BUFFER_SIZE` değerleri ve Valgrind testleriyle kontrol edildi.

Projenin çalışma mantığı, kullanılan fonksiyonlar ve teslim edilen kod öğrenci
tarafından incelenmiş, test edilmiş ve anlaşılmıştır.
