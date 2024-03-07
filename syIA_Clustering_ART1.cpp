#include <iostream>

using namespace std;

const int NSAMP = 22;
const int NFEAT = 10;

const int inputs[NSAMP][NFEAT+1] =
        {
                {1,0,0,0,0,1,1,0,1,1,-1}, // Sample 0
                {1,0,1,1,0,0,1,0,1,1,-1}, // Sample 1
                {1,0,1,1,1,0,0,1,1,0,-1}, // Sample 2
                {1,0,1,1,1,1,0,1,1,1,-1}, // Sample 3
                {1,0,1,1,0,1,1,1,0,0,-1}, // Sample 4

                {1,1,1,1,1,1,1,1,1,1,-1}, // Sample 5
                {1,0,1,0,1,1,1,1,0,1,-1}, // Sample 6
                {1,1,1,0,1,1,1,1,0,0,-1}, // Sample 7
                {1,0,0,1,1,1,1,0,0,0,-1}, // Sample 8
                {1,0,0,1,0,0,1,1,1,0,-1}, // Sample 9

                {1,1,1,1,1,1,0,0,1,0,-1}, // Sample 10
                {1,0,0,1,1,0,0,0,1,1,-1}, // Sample 11
                {1,1,1,0,1,1,0,1,1,1,-1}, // Sample 12
                {0,0,0,1,0,1,1,0,0,1,-1}, // Sample 13
                {0,1,1,1,0,0,1,1,1,1,-1}, // Sample 14

                {1,0,1,0,1,1,1,0,1,1,-1}, // Sample 15
                {1,0,1,0,0,1,1,0,0,1,-1}, // Sample 16
                {1,0,   1,1,1,1,1,0,1,0,-1}, // Sample 17
                {1,1,0,1,1,1,1,0,1,1,-1}, // Sample 18
                {1,1,0,1,0,1,1,0,0,1,-1}, // Sample 19

                {1,1,1,1,0,0,1,0,1,1,-1}, // Sample 20
                {1,0,0,0,1,0,1,0,1,0,-1}  // Sample 21
        };

class ART1
{
    int **E;
    int **P;
    int nPrototypes;
    float beta;
    float rho;

public:
    ART1(float beta, float rho): beta(beta), rho(rho) {
        E = new int*[NSAMP];
        for(int i = 0; i < NSAMP; ++i)
            E[i] = new int[NFEAT+1]();

        for (int i = 0; i < NSAMP; ++i)
            for (int j = 0; j < NFEAT+1; ++j)
                E[i][j] = inputs[i][j];

        P = syMatrixNew(NSAMP, NFEAT);
        nPrototypes = 0;
        syVectorCopyTo(E[0],P[0],NFEAT);
        E[0][NFEAT] = 0;
        nPrototypes++;
    }

    int syProximityTest(int *E,int *P, int nD, float beta)
    {
        int vAnd[25];
        syVectorAnd(E,P,vAnd,nD);
        int mag = syVectorMagnitude(vAnd,nD);

        float termL = mag/(beta+syVectorMagnitude(P,nD));
        float termR = syVectorMagnitude(E,nD)/(beta+nD);

        if (termL > termR) return 1;
        return 0;
    }

    int syVigilanceTest(int *E,int *P, int nD, float rho)
    {
        int vAnd[25];
        syVectorAnd(E,P,vAnd,nD);
        int mag = syVectorMagnitude(vAnd,nD);

        float termL = (float) mag/syVectorMagnitude(E,nD);

        if (termL >= rho) return 1;
        return 0;
    }

    int syVectorMagnitude(int *v, int nD)
    {
        int mag = 0;
        for (int k=0; k<nD; k++)
            mag += v[k];
        return mag;
    }

    int syVectorAnd(int *v1, int *v2, int *vA, int nD)
    {
        for (int k=0; k<nD; k++)
            if(v1[k]==1 && v2[k]==1) vA[k]=1;
            else vA[k]=0;
        return 0;
    }

    int syVectorCopyTo(int *S, int *D, int nD)
    {
        for (int k=0; k<nD; k++)
            D[k] = S[k];
        return 0;
    }

    int syVectorMergeInProto(int *E, int *P, int nD)
    {
        for (int k=0; k<nD; k++)
            if(E[k]==0 || P[k]==0) P[k]=0;

        return 0;
    }

    int syVectorDisplay(int *v, int nD)
    {
        for (int k=0; k<nD; k++)
            cout << v[k] << " ";
        cout << "\n";
        return 0;
    }

    int **syMatrixNew(int nR, int nC)
    {
        int **M;
        M = new int *[nR];

        for (int k=0; k<nR; k++)
            M[k] = new int[nC];

        for (int r=0; r<nR; r++)
            for (int c=0; c<nC; c++)
                M[r][c] = 0;

        return M;
    }

    int syMatrixDelete(int **M, int nR)
    {
        for (int r=0; r<nR; r++)
            delete[] M[r];
        delete[] M;
        return 0;
    }

    void generateRecommendations()
    {
        for (int r=0; r<nPrototypes; r++)
        {
            int clusterSize = 0;
            for (int s=0; s<NSAMP; s++)
                if (E[s][NFEAT] == r)
                    clusterSize++;

            if (clusterSize >= 4)
            {
                cout << "\nCluster " << r << " has " << clusterSize << " elements. Generating recommendations...\n";
                for (int s=0; s<NSAMP; s++)
                {
                    if (E[s][NFEAT] == r)
                    {
                        for (int f=0; f<NFEAT; f++)
                        {
                            if (E[s][f] == 0)
                            {
                                bool allOthersHaveFeature = true;
                                for (int t=0; t<NSAMP; t++)
                                {
                                    if (E[t][NFEAT] == r && t != s && E[t][f] == 0)
                                    {
                                        allOthersHaveFeature = false;
                                        break;
                                    }
                                }
                                if (allOthersHaveFeature)
                                {
                                    cout << "Sample " << s << " might consider feature " << f << " as all other members in the cluster have it.\n";
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    void run()
    {
        for (int m=0; m<NSAMP; m++)
        {
            int merged = 0;
            for (int n=0; n<nPrototypes; n++)
            {
                if (syProximityTest(E[m],P[n],NFEAT, beta) && syVigilanceTest(E[m],P[n],NFEAT, rho) )
                {
                    syVectorMergeInProto(E[m], P[n], NFEAT) ;
                    E[m][NFEAT] = n;
                    merged = 1;
                    break;
                }
            }
            if (!merged && nPrototypes < NSAMP) // Asegúrate de que nPrototypes es menor que NSAMP
            {
                syVectorCopyTo(E[m],P[nPrototypes],NFEAT);
                E[m][NFEAT] = nPrototypes;
                nPrototypes++;
            }
        }

        cout << "\n\n\nFinally, "<<nPrototypes<< " clusters were found.\n";
        for (int r=0; r<nPrototypes; r++)
        {
            cout << "\nCluster    ";
            syVectorDisplay(P[r],NFEAT);
            cout << "includes\n";
            for (int s=0; s<NSAMP; s++)
                if (E[s][NFEAT] == r)
                {
                    printf("Sample %2d: ",s);
                    syVectorDisplay(E[s],NFEAT);
                }
        }

        generateRecommendations();

        syMatrixDelete(P,NSAMP);
        cout << "\n\nTo continue, press <Enter>. ";
        cin.get();
    }
};

int main(void)
{
    ART1 art1(3.0, 0.10);
    art1.run();
    return 0;
}
