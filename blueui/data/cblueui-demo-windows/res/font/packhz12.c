/*pack12hz.c for HAVE_BIG5_SUPPORT*/
/*convert fonts/chinese/hzx12 to fonts/chinese/big5font.c*/
#include <stdio.h>

#define SIZEHZX12 324048

char head[] =
{
"/* %s %dx%d font Raster data\n"
"*/\n"
"\n"
"#include \"CGlyphRaster.h\"\n"
"unsigned char FONT_BITMAP_%s_%dX%d[] = {\n"
};

char tail[] = "};\n";

void fprintbit(FILE* fp, char* s, int count)
{
	int i, j;
	char* b = s, t;

	for (i = 0; i < count; i++)
	{
		t = *b;
		for (j = 0; j < 8; j++)
		{
			if (t & 0x80)
				fprintf(fp, "*");
			else
				fprintf(fp, ".");
			t <<= 1;
		}
		b++;
	}
}


void packTohz(const char* font, const char* outfile, const char* varname, int w, int h)
{
	FILE* fp, * fp2;
	char* buf, * s;
	unsigned char p3[4];
	int i;

	printf("pack12hz v0.1 2k0816 by kevin@gv.com.tw\n");

	printf("loading %s...", font);
	fp = fopen(font, "rb");
	if (!fp)
	{
		printf("error open hzx12\n");
		return 1;
	}


	fseek(fp, 0, SEEK_END);
	long filelength = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	buf = (char*)malloc(filelength);
	if (!buf)
	{
		printf("error malloc(%d)\n", filelength);
		fclose(fp);
		return 2;
	}
	fread(buf, 1, filelength, fp);
	fclose(fp);
	printf("ok\n");

	printf("%s -> %s ...", font, outfile);
	fflush(stdout);

	char bufer[125] = { 0 };
	sprintf(bufer, "FONT_%s_%dX%d.cpp", varname, w, h);
	fp2 = fopen(bufer, "wt+");
	fprintf(fp2, head, varname, w, h,varname, w, h);
	s = buf;

	if (w <= 8)
	{
		for (i = 0; i < filelength; i++)
		{
			if (!(i % (h)) && i)
				fprintf(fp2, "\n");
			p3[0] = *s;
			fprintf(fp2, "\t0x%02x,\t/* ", p3[0]);
			fprintbit(fp2, s, 1);
			fprintf(fp2, " */\n");
			s+=1;
		}
	}
	else
	{
		for (i = 0; i < (filelength / 4); i++)
		{
			p3[0] = *s;
			p3[1] = (*(s + 1) & 0xf0) + ((*(s + 3) & 0xf0) >> 4);
			p3[2] = *(s + 2);

			p3[0] = *s;
			p3[1] = *(s+1);
			p3[2] = *(s + 2);
			p3[3] = *(s + 3);
			if (!(i % (h / 2)) && i)
				fprintf(fp2, "\n");

			fprintf(fp2, "\t0x%02x, 0x%02x,\t/* ", p3[0], p3[1]);
			fprintbit(fp2, s, 2);
			fprintf(fp2, " */\n");

			fprintf(fp2, "\t0x%02x, 0x%02x,\t/* ", p3[2], p3[3]);
			fprintbit(fp2, s + 2, 2);
			fprintf(fp2, " */\n");

			s += 4;
		}
	}


	fprintf(fp2, tail);
	fclose(fp2);
	printf("ok\n");
}

int main(int argc, char** argv)
{
	
	packTohz("hzk12", "font_gb2312_12x12.c", "GB2312", 12, 12);
	packTohz("hzk16", "font_gb2312_16x16.c", "GB2312", 16, 16);
	packTohz("hzx12", "font_big5_16x12.c", "BIG5", 16, 12);
	packTohz("hzk16", "font_big5_16x16.c", "BIG5", 16, 16);

	packTohz("asc12", "font_asc8x12.c", "ASC", 8, 12);
	packTohz("asc16", "font_asc8x16.c", "ASC", 8, 16);
	return 0;
}
