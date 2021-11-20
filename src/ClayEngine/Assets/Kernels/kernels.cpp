
void kernel surfaceKernel(global int* a, global int* b, global int* c)
{

   int gid = get_global_id(0);

   if(gid==0) printf("SurfaceKernel\n");

   c[gid] = gid*gid;



}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

