#include "hnm.h"

/**
 * get_elf - get ELF infos
 * @fp: pointer to file stream
 * @filename: name of binary
 * @arg: pointer to that name
 * @ret: current exit status
 */

void get_elf(FILE *fp, char *filename, char *arg, int *ret)
{
	struct stat sb;
	hdrs hdr;

	/* prepare memory place */
	memset(&hdr, 0, sizeof(hdr));
	if (stat(arg, &sb))
		goto printerr;

	hdr.map = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fileno(fp), 0);
	if (hdr.map == MAP_FAILED)
	{
	printerr:
		perror(NULL);
		goto out;
	}
	init_ehdr(&hdr);
	if (memcmp(hdr.Ehdr64->e_ident, ELFMAG, SELFMAG))
	{
		fprintf(stderr, "%s: %s: file format not recognized\n", filename, arg);
	out:
		*ret = 1;
		fclose(fp);
		return;
	}
	init_shdr(&hdr);
	if (!sym(&hdr))
		fprintf(stderr, "%s: %s: no symbols for this binary\n", filename, arg);
	fclose(fp);
}

/**
 * parse_args - parse argument and try to open
 * @argc: argument count
 * @argv: argument vector
 * @idx: index or argv[]
 * Return: pointer to file stream , or NULL if failure
 */

FILE *parse_args(int argc, char **argv, int idx)
{
	FILE *fp;
	struct stat sb;

	/* default behavior of nm if argv[1] is NULL */
	/* look for "a.out" and nm's it */
	if (argc == 1)
		argv[1] = "a.out";
	stat(argv[idx], &sb);
	if (S_ISDIR(sb.st_mode))
	{
		fprintf(stderr, "Warning: can't nm a directory\n");
		return (NULL);
	}
	fp = fopen(argv[idx], "rb");
	if (!fp)
	{
		fprintf(stderr, "%s: '%s': No such file", argv[0], argv[idx]);
		return (NULL);
	}
	return (fp);
}

/** main - entry point of program, eats argument and lets go
 * @argc - argument count
 * @argv: argument vector
 * Return: int ret as an exit status
 */

int main(int argc, char **argv)
{
	FILE *fp;
	int ret = 0, i = 1;

	while (i < argc)
	{
		fp = parse_args(argc, argv, i);
		if (!fp)
			ret = 1;
		get_elf(fp, argv[0], argv[i], &ret);
		i++;
	}
	return (ret);
}
